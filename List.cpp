#include "List.h"


// =====================================    // Private

int ArrList::OpenFile(FILE** file, const char* filename, const char* mode)
{
    *file = fopen(filename, mode);

    DEBUG
    {
        if(file == nullptr)
            fprintf(stderr, "\x1b[31mOpenFile(): failed to open file \"%s\" in \"%s\" mode\x1b[0m\n", filename, mode);
        else
            fprintf(stderr, "\x1b[32mOpenFile(): succsessfuly opened file \"%s\" in \"%s\" mode\x1b[0m\n", filename, mode);
    }
    return (file != nullptr)?   SUCCESS : FILE_NOT_OPENED;
}

int ArrListOk()
{
    //
}

// =====================================    // Public

ArrList::ArrList()
{
    txt_log_status = OpenFile(&txt_log, TXT_LOG_NAME, "w");
    img_log_status = OpenFile(&img_log, IMG_LOG_SOURCE_NAME, "w");

    if(txt_log != nullptr){
        PrintLog("txt_log successfuly opened in constructor\n");

        if(img_log != nullptr)
            PrintLog("img_log successfuly opened in constructor\n");
        else
            PrintLog("OpenFile() failed to open img_log in constructor\n");
    }

    elements[0].data = NULL_ELEM;
    elements[0].next = 0;
    elements[0].prev = 0;

    elements[1].data = NULL_ELEM;
    elements[1].next = 2;
    elements[1].prev = 0;

    for(int i = 2; i < MAX_ELEMENTS; i++){
        elements[i].next = i + 1;
        elements[i].prev = NO_PTR;
    }

    elements[MAX_ELEMENTS - 1].next = 0;
    elements[MAX_ELEMENTS - 1].prev = NO_PTR;

    PrintLog("Constructor(): elements filled\n");
    DEBUG fprintf(stderr, "Constructor(): elements filled\n");
}

int ArrList::AddElemAfter (int after_which, data_t data)
{
    PrintLog("\nCalling AddElemAfter()\n");
    DEBUG fprintf(stderr, "\nCalling AddElemAfter():\nafter_which = %d\n", after_which);

    assert(after_which > 0);
    assert(after_which < MAX_ELEMENTS);

    // Check if user does not try to work with empty space
    if(elements[after_which].prev == NO_PTR){
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", after_which);
        PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");
        return ELEMENT_IS_EMPTY;
    }

    if(elements[free].next == NULL_PTR){
        DEBUG fprintf(stderr, "\x1b[31mList is full, can not add any element\x1b[0m\n");
        PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");
        return LIST_OVERFLOW;
    }

    //  ============================================

    printf("elements[after_which].next = %d\n", elements[after_which].next);

    int new_free = elements[free].next;
    int new_elem_pos = free;
    printf("new free = %d\n", new_free);

    // !!!!!
    if(after_which != tail)
        elements[new_elem_pos].next = elements[after_which].next;
    else{
        elements[new_elem_pos].next = elements[free].next;
    }
    // !!!!!

    elements[new_elem_pos].prev = after_which;
    elements[new_elem_pos].data = data;

    // Remembering pointer to last elem in this trio
    int old_after_which_next = elements[after_which].next;

    //elements[after_which].next = /*new_elem_pos*/free;
    elements[old_after_which_next].prev = new_elem_pos;

    printf("and after: elements[after_which].next = %d\n", elements[after_which].next);
    free = new_free;

    DEBUG fprintf(stderr, "\x1b[32mElement added: position = %d\x1b[0m\n", new_elem_pos);
    printf("new elem: elements[%d].prev = %d\n", new_elem_pos, elements[new_elem_pos].prev);
    printf("old elem: elements[%d].prev = %d\n", old_after_which_next, elements[old_after_which_next].prev);

    //  ============================================

    if(after_which == tail)
        tail = new_elem_pos;
    printf("tail = %d\n", tail);


    PrintLog("Quiting AddElemAfter()\n");
    DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");

    return SUCCESS;
}

int ArrList::AddElemBefore(int before_which, data_t data)
{
    PrintLog("\nCalling AddElemBefore()\n");
    DEBUG fprintf(stderr, "\nCalling AddElemBefore():\nbefore_which = %d\n", before_which);

    assert(before_which > 0);
    assert(before_which < MAX_ELEMENTS);

    // Check if user does not try to work with empty space
    if(elements[before_which].prev == NO_PTR){
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", before_which);
        PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");
        return ELEMENT_IS_EMPTY;
    }

    if(elements[free].next == NULL_PTR){
        DEBUG fprintf(stderr, "\x1b[31mList is full, can not add any element\x1b[0m\n");
        PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");
        return LIST_OVERFLOW;
    }

    //  ============================================

    int new_free = elements[free].next;
    int new_elem_pos = free;

    elements[new_elem_pos].next = before_which;
    elements[new_elem_pos].prev = elements[before_which].prev;
    elements[new_elem_pos].data = data;

    // Remembering pointer to last elem in this trio
    int old_before_which_prev = elements[before_which].prev;

    elements[before_which].prev = new_elem_pos;
    elements[old_before_which_prev].next = new_elem_pos;

    free = new_free;

    DEBUG fprintf(stderr, "\x1b[32mElement added: position = %d\x1b[0m\n", new_elem_pos);

    //  ============================================

    if(before_which == head)
        head = new_elem_pos;

    PrintLog("Quiting AddElemBefore()\n");
    DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

    return SUCCESS;
}

int ArrList::DelElemAfter (int after_which)
{
    PrintLog("\nCalling DelElemAfter()\n");
    DEBUG fprintf(stderr, "\nCalling DelElemAfter():\nafter_which = %d\n", after_which);

    assert(after_which > 0);
    assert(after_which < MAX_ELEMENTS);

    // Check if user does not try to work with empty space
    if(elements[after_which].prev == NO_PTR){
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", after_which);
        PrintLog("Quiting DelElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");
        return ELEMENT_IS_EMPTY;
    }

    if(after_which == tail){
        DEBUG fprintf(stderr, "\x1b[31mNext element does not exist, can not delete it\x1b[0m\n");
        PrintLog("Quiting DelElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");
        return ELEMENT_DOES_NOT_EXIST;
    }

    //  ============================================

    int del_elem_pos = elements[after_which].next;

    // Remembering pointer to last elem in this trio
    int del_next = elements[del_elem_pos].next;

    elements[after_which].next = elements[del_elem_pos].next;
    elements[del_next].prev = after_which;

    elements[del_elem_pos].next = free;
    elements[del_elem_pos].prev = NO_PTR;
    elements[del_elem_pos].data = NULL_ELEM;

    free = del_elem_pos;

    DEBUG fprintf(stderr, "\x1b[32mElement deleted: position = %d\x1b[0m\n", del_elem_pos);

    //  ============================================

    if(del_elem_pos == tail)
        tail = after_which;

    PrintLog("Quiting DelElemAfter()\n");
    DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");

    return SUCCESS;
}

int ArrList::DelElemBefore(int before_which)
{
    PrintLog("\nCalling DelElemBefore()\n");
    DEBUG fprintf(stderr, "\nCalling DelElemBefore():\nbefore_which = %d\n", before_which);

    assert(before_which > 0);
    assert(before_which < MAX_ELEMENTS);

    // Check if user does not try to work with empty space
    if(elements[before_which].prev == NO_PTR){
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", before_which);
        PrintLog("Quiting AddElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");
        return ELEMENT_IS_EMPTY;
    }

    if(before_which == head){
        DEBUG fprintf(stderr, "\x1b[31mPrevious element does not exist, can not delete it\x1b[0m\n");
        PrintLog("Quiting AddElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");
        return ELEMENT_DOES_NOT_EXIST;
    }

    //  ============================================

    int del_elem_pos = elements[before_which].prev;

    // Remembering pointer to last elem in this trio
    int del_prev = elements[del_elem_pos].prev;

    elements[before_which].prev = elements[del_elem_pos].prev;
    elements[del_prev].next = before_which;

    elements[del_elem_pos].next = free;
    elements[del_elem_pos].prev = NO_PTR;
    elements[del_elem_pos].data = NULL_ELEM;

    free = del_elem_pos;

    DEBUG fprintf(stderr, "\x1b[32mElement deleted: position = %d\x1b[0m\n", del_elem_pos);

    //  ============================================

    if(del_elem_pos == head)
        head = before_which;

    PrintLog("Quiting AddElemAfter()\n");
    DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");

    return SUCCESS;
}

// =========================    // Dumps

int ArrList::PrintLog(char* info)
{
    int res = 0;
    if(txt_log_status != FILE_NOT_OPENED)
        res = fprintf(txt_log, info);
    return res;
}

int ArrList::WriteDotImg(FILE* img_dot_source)
{
    assert(img_dot_source != nullptr);

    PrintLog("\nCalling WriteDotImg()\n");
    DEBUG fprintf(stderr, "\nCalling WriteDotImg()\n");

    fprintf(img_dot_source, BEGIN);
    fprintf(img_dot_source, SET_RECORD_SHAPE);

    // Filling info about elements
    int i = head;
    while(i != tail){
        fprintf(img_dot_source, "%d", i);

        fprintf(img_dot_source, BEGIN_DECLARATION);
        fprintf(img_dot_source, LABELS);
        fprintf(img_dot_source, NEXT_FIELD);

        fprintf(img_dot_source, BEGIN_COLUMN);
        fprintf(img_dot_source, "%d", i);
        fprintf(img_dot_source, NEXT_FIELD);
        fprintf(img_dot_source, "%d", elements[i].data);
        fprintf(img_dot_source, NEXT_FIELD);
        fprintf(img_dot_source, "%d", elements[i].next);
        fprintf(img_dot_source, NEXT_FIELD);
        fprintf(img_dot_source, "%d", elements[i].prev);
        fprintf(img_dot_source, END_COLUMN);

        fprintf(img_dot_source, END_DECLARATION);

        i = elements[i].next;
    }
    fprintf(img_dot_source, "%d", i);

    fprintf(img_dot_source, BEGIN_DECLARATION);
    fprintf(img_dot_source, LABELS);
    fprintf(img_dot_source, NEXT_FIELD);

    fprintf(img_dot_source, BEGIN_COLUMN);
    fprintf(img_dot_source, "%d", i);
    fprintf(img_dot_source, NEXT_FIELD);
    fprintf(img_dot_source, "%d", elements[i].data);
    fprintf(img_dot_source, NEXT_FIELD);
    fprintf(img_dot_source, "%d", elements[i].next);
    fprintf(img_dot_source, NEXT_FIELD);
    fprintf(img_dot_source, "%d", elements[i].prev);
    fprintf(img_dot_source, END_COLUMN);

    fprintf(img_dot_source, END_DECLARATION);

    // Setting connections
    i = head;
    while(i != tail){
        int next = elements[i].next;
        fprintf(img_dot_source, "%d", i);
        fprintf(img_dot_source, TO);
        fprintf(img_dot_source, "%d", next);
        fprintf(img_dot_source, FORWARD_DIRECTION);

        fprintf(img_dot_source, "%d", next);
        fprintf(img_dot_source, TO);
        fprintf(img_dot_source, "%d", elements[next].prev);
        if(elements[next].prev == i)
            fprintf(img_dot_source, BACK_DIRECTION);
        else
            fprintf(img_dot_source, WRONG_DIRECTION);

        i = elements[i].next;
    }

    fprintf(img_dot_source, END);

    PrintLog("Quiting WriteDotImg()\n");
    DEBUG fprintf(stderr, "Quiting WriteDotImg()\n");
}

int ArrList::CompileDotImg(const char* text, const char* img)
{
    PrintLog("\nCalling CompileDotImg()\n");
    DEBUG fprintf(stderr, "\nCalling CompileDotImg()\n");

    char command[1000];
    strcpy(command, DOT1);
    strcat(command, text);
    strcat(command, DOT2);
    strcat(command, img);

    DEBUG fprintf(stderr, "Closing img_log in CompileDotImg():\n");
                 PrintLog("Closing img_log in CompileDotImg():\n");
    fclose(img_log);
    DEBUG fprintf(stderr, "img_log closed in CompileDotImg()\n");
                 PrintLog("img_log closed in CompileDotImg()\n");

    DEBUG fprintf(stderr, "Command to execute in CompileDotImg(): \"%s\"\n", command);
                 PrintLog("Command to execute in CompileDotImg(): \"");
                 PrintLog(command);
                 PrintLog("\"\n");

    PrintLog("Quiting CompileDotImg()\n");
    DEBUG fprintf(stderr, "Quiting CompileDotImg()\n");
    return system(command);
}

int ArrList::CallDumpImg(const char* img)
{
    PrintLog("\nCalling CallDumpImg()\n");
    DEBUG fprintf(stderr, "\nCalling CallDumpImg()\n");

    char command[1000];
    strcpy(command, OPEN);
    strcat(command, img);

    int res = system(command);
    DEBUG fprintf(stderr, "Command to execute in CallDumpImg(): |%s|\n", command);
                 PrintLog("Command to execute in CallDumpImg(): \"");
                 PrintLog(command);
                 PrintLog("\"\n");

    DEBUG fprintf(stderr, "Opening img_log in CallDumpImg():\n");
                 PrintLog("Opening img_log in CallDumpImg():\n");
    if(!OpenFile(&img_log, TXT_LOG_NAME, "w"))
        PrintLog("img_log opened in CallDumpImg()\n");
    else
        PrintLog("OpenFile() failed to open img_log in CallDumpImg()\n");

    PrintLog("Quiting CallDumpImg()\n");
    DEBUG fprintf(stderr, "Quiting CallDumpImg()\n");
    return res;
}

int ArrList::CallImg()
{
    WriteDotImg(img_log);
    CompileDotImg(IMG_LOG_SOURCE_NAME, IMG_LOG_RESULT_NAME);
    CallDumpImg(IMG_LOG_RESULT_NAME);
}

