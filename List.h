#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Errors.h"
#include "DotSyntax.h"


// =====================================================    //  Assert define

#define ARR_LIST_ASSERT()                                                       \
    do{                                                                     \
        int err = ArrListOk();                                              \
        if(err != SUCCESS){                                                 \
            DEBUG fprintf(stderr, "\x1b[31m\nASSERTION FAILED!\x1b[0m\n");  \
            Dump(err, __func__);                                            \
            CallImg();                                                      \
            fclose(img_log);                                                \
            fclose(txt_log);                                                \
            assert(0);                                                      \
        }                                                                   \
    }while(0)

// =====================================================    //  Debug modes
//
// Comment next line if you want to remove debug
//#define _DEBUG
#if defined (_DEBUG)
    #define DEBUG
#else
    #define DEBUG if(0)
#endif // defined

// Comment next line if you want to remove debug print in assert
//#define _VER
#if defined (_VER)
    #define VER_PRINT
#else
    #define VER_PRINT if(0)
#endif // defined

// Comment next line if you want to remove SUPER-debug
//#define _SUPER_DEBUG
#if defined (_SUPER_DEBUG)
    #define SUPER_DEBUG
#else
    #define SUPER_DEBUG if(0)
#endif // defined

// Comment next line if you want to remove LOG_WRITE
//#define _LOG_WRITE
#if defined (_LOG_WRITE)
    #define LOG_WRITE
#else
    #define LOG_WRITE if(0)
#endif // defined

// =====================================================    //  Supporting defines

/// Prints name and value of an integer
#define PrintVarriable( var )                   \
    do{                                         \
        DEBUG fprintf(stderr, "\x1b[33m");      \
        DEBUG fprintf(stderr, #var);            \
        DEBUG fprintf(stderr, " = %d\n", var);  \
        DEBUG fprintf(stderr, "\x1b[0m");       \
    }while(0)                                   \

// =====================================================    //  Global constants

const char TXT_LOG_NAME[]        = "log.txt";   // Writing text debug
const char IMG_LOG_SOURCE_NAME[] = "log.dot";   // Writing DOT debug
const char IMG_LOG_RESULT_NAME[] = "log.ps";    // Creating image with this name

/// Max amount of elements in the list
const int MAX_ELEMENTS = 100;

//typedef int data_t;
typedef char data_t;


/// Value of data in an empty element
const data_t NULL_ELEM[] = "NuLl";

/// Value of pointer in NULL element
const int     NULL_PTR = 0;

/// Value of prev-pointer in an empty element
const int       NO_PTR = -1;

// =====================================================    //  Class definition

struct ArrListElem {
    data_t data[100];// = NULL_ELEM;
    int next    = 0;
    int prev    = 0;
};

class ArrList {
//private:
public:
// Main attributes

    /// Array with elements
    ArrListElem elements[MAX_ELEMENTS];

    /// "Pointer" to the first element
    int head   = 1;

    /// "Pointer" to the last element
    int tail   = 1;

    /// "Pointer" to the first free element
    int free   = 2;

    /// Amount of elements element
    int n_elem = 1;

// Supporting attributes

    /// File with code for DOT
    FILE* img_log = nullptr;

    /// File with text logs
    FILE* txt_log = nullptr;

    /// Statuses of log files
    int img_log_status = FILE_NOT_OPENED;
    int txt_log_status = FILE_NOT_OPENED;

// Supporting functions

    /// Opens file
    /**
        Returns SUCCESS in case of success, FILE_NOT_OPENED in other case.

        \param [out]    file    Pointer to the file to be opened
        \param [in] filename    Name ot the file to be opened
        \param [in]     mode    Mode of the file to be opened

    */
    int OpenFile(FILE** file, const char* filename, const char* mode);

// Verificator
    int ArrListOk();                                // =====================================    FIX

    /// Checks if such element exists
    /**
        \param [in] elem_pos    "Pointer" to the element we want to check
    */
    bool ElemExists(int elem_pos);

    /// Checks if List is owerflown
    bool ListOwerflown();

public:

    /// Constructor
    ArrList();

    /// Adds element after given one
    /**
        Returns SUCCESS in case of success, error code otherwise.

        \param [in] after_which "Pointer" to the element to be after the new element
        \param [in] data        Data to be placed in the new element
    */
//    int AddElemAfter (int after_which, data_t data);
    int AddElemAfter (int after_which, data_t data[]);

    /// Adds element before given one
    /**
        Returns SUCCESS in case of success, error code otherwise.

        \param [in] before_which    "Pointer" to the element to be before the new element
        \param [in] data            Data to be placed in the new element
    */
//    int AddElemBefore(int before_which, data_t data);
    int AddElemBefore(int before_which, data_t data[]);

    /// Adds element after given one
    /**
        Returns SUCCESS in case of success, error code otherwise.

        \param [in] after_which "Pointer" to the element to be after the element to delete
    */
    int DelElemAfter (int after_which);

    /// Adds element after given one
    /**
        Returns SUCCESS in case of success, error code otherwise.

        \param [in] before_which "Pointer" to the element to be before the element to delete
    */
    int DelElemBefore(int before_which);

    /// Sets data in element
    /**
        \param [in] elem_pos    "Pointer" to the element
        \param [in] data        Data to be set
    */
//    int SetData(int elem_pos, data_t data);
    int SetData(int elem_pos, data_t data[]);

    /// Gets data from element
    /**
        Places data to elem_data. Returns SUCCESS in case of success, error code othewise

        \warning data = nullptr in case of error!

        \param [in] elem_pos    "Pointer" to the element we want to explore
        \param [in] elem_data   Address of the varriable where we want to get data
    */
//    int GetElemData(int elem_pos, data_t* elem_data);
    int GetElemData(int elem_pos, data_t* elem_data[]);

    /// Returns pointer to the next element
    int GetNext(int elem_pos);

    /// Returns head
    int GetHead();

    /// Returns tail
    int GetTail();

// =========================    // Dumps

    /// Classical dump. Prints in txt_log and on the screen.
    /**
        \param [in] err_code    Error code. SUCCESS be default (everything is ok, nothing is broken)
        \param [in] func        Name of the fuction that called Dump()
    */
    int Dump(int err_code = SUCCESS, const char* func = __func__);

    /// Prints logs to the text log file
    /**
        \param [in] info    Information to be printed in logs
    */
    int PrintLog(const char* info);

    /// Prints List's arguments
    /**
        Returns amount of printed attributes.
    */
    int PrintListAttributes();

    /// Creates file with code for DOT
    /**
        Returns the same value as system() returns.

        \param [in] img_dot_sourse  File with sources for DOT
    */
    int WriteDotImg(FILE* img_dot_source);

    /// Compiles file with code for DOT in an image
    /**
        Returns the same value as system() returns.

        \param [in] text    Name of the file with code for DOT
        \param [in] img     Name of the file with compiled image
    */
    int CompileDotImg(const char* text, const char* img);

    /// Opens dump image
    /**
        Returns the same value as system() returns.

        \param [in] img     Name of the file with image
    */
    int CallDumpImg  (const char* img);

    /// Calls WriteDotImg(), CompileDotImg() and CallDumpImg() in this order
    /**
        Returns the same value as system() returns.
    */
    int CallImg();

// =========================    // Slow ?

    /// Finds "pointer" to the element by its logical position
    /**
        Returns "pointer" to the element.

        \param [in] logical_pos Logical position of the element to be found
    */
    int FindElemSlow(int logical_pos);
};


#endif // LIST_H_INCLUDED
