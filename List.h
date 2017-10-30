#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "Errors.h"
#include "DotSyntax.h"


// =====================================================    //  Debug mode
//
// Comment next line if you want to remove debug
#define _DEBUG
#if defined (_DEBUG)
    #define DEBUG
#else
    #define DEBUG if(0)
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

const int MAX_ELEMENTS = 100;

typedef int data_t;
const data_t NULL_ELEM = -123456;
const int     NULL_PTR = 0;
const int       NO_PTR = -1;

// =====================================================    //  Class definition

struct ArrListElem {
    data_t data = NULL_ELEM;
    int next    = 0;
    int prev    = 0;
};

class ArrList {
//private:
public:
// Main attributes
    ArrListElem elements[MAX_ELEMENTS];
    int head = 1;
    int tail = 1;
    int free = 2;

// Supporting attributes
    FILE* img_log = nullptr;
    FILE* txt_log = nullptr;
    int img_log_status = FILE_NOT_OPENED;
    int txt_log_status = FILE_NOT_OPENED;

// Supporting functions
    int OpenFile(FILE** file, const char* filename, const char* mode);

// Verificator
    int ArrListOk();                                // =====================================    FIX

public:
    ArrList();

    int AddElemAfter (int after_which, data_t data);    //  FFIIXX!!!!!!!!!!!!
    int AddElemBefore(int before_which, data_t data);   //  AND CHECK OTHER!!!!!!!!!!
    int DelElemAfter (int after_which);                 //  WHAT IF TAIL OF HEAD!?
    int DelElemBefore(int before_which);

// =========================    // Dumps

    int PrintLog(char* info);
    int PrintListAttributes();

    int WriteDotImg(FILE* img_dot_source);          // =====================================    FIX

    int CompileDotImg(const char* text, const char* img);
    int CallDumpImg  (const char* img);

    int CallImg();
};

#endif // LIST_H_INCLUDED
