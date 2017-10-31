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

int ArrList::ArrListOk()
{
    VER_PRINT fprintf(stderr, "\n\x1b[34m-----VERIFICATOR ENTERED-----\x1b[0m");
    VER_PRINT LOG_WRITE PrintLog("\n-----Calling ArrListOk()-----\n");
    VER_PRINT fprintf(stderr, "\n-----Calling ArrListOk()-----\n");

    // Check if List is looped
    int i = head;
    int steps = 0;
    while(i != tail){
        if(steps > n_elem){
            VER_PRINT fprintf(stderr, "\x1b[31m-----LOOKS LIKE LIST IS LOOPED!!!-----\n\x1b[0m");
            VER_PRINT LOG_WRITE PrintLog("-----LOOKS LIKE LIST IS LOOPED!!!-----\n");

            VER_PRINT fprintf(stderr, "\x1b[34m-----VERIFICATOR QUITED-----\n\x1b[0m");
            return LIST_LOOPED;
        }
        i = elements[i].next;
        steps++;
    }

    // Check if next and prev are ok
    VER_PRINT PrintVarriable(head);

    if(n_elem > 1){
        i = elements[head].next;
        while(i != tail){
            int me = elements[elements[i].prev].next;

            VER_PRINT PrintVarriable(me);
            VER_PRINT PrintVarriable(i);

            if(me != i){
                VER_PRINT fprintf(stderr, "\x1b[31m-----LOOKS LIKE LIST CONNECTIONS ARE WRONG!!!-----\n\x1b[0m");
                VER_PRINT LOG_WRITE PrintLog("-----LOOKS LIKE LIST CONNECTIONS ARE WRONG!!!-----\n");

                VER_PRINT fprintf(stderr, "\x1b[34m-----VERIFICATOR QUITED-----\n\x1b[0m");
                return CONNECTION_WRONG;
            }
            i = elements[i].next;
        }
    }

    VER_PRINT fprintf(stderr, "\x1b[32m-----LIST IS OK-----\n\x1b[0m");
    VER_PRINT LOG_WRITE PrintLog("-----LIST IS OK-----\n");

    VER_PRINT LOG_WRITE PrintLog("-----Quiting ArrListOk()-----\n");
    VER_PRINT fprintf(stderr, "-----Quiting ArrListOk()-----\n");

    VER_PRINT fprintf(stderr, "\x1b[34m-----VERIFICATOR QUITED-----\n\x1b[0m");

    return SUCCESS;
}

bool ArrList::ElemExists(int elem_pos)
{
    return (elements[elem_pos].prev == NO_PTR)?  false : true;
}

bool ArrList::ListOwerflown()
{
    return (elements[free].next == NULL_PTR)?  true : false;
}

// =====================================    // Public

ArrList::ArrList()
{
    txt_log_status = OpenFile(&txt_log, TXT_LOG_NAME, "w");
    img_log_status = OpenFile(&img_log, IMG_LOG_SOURCE_NAME, "w");

    if(txt_log != nullptr){
        LOG_WRITE PrintLog("txt_log successfuly opened in constructor\n");

        if(img_log != nullptr)
            LOG_WRITE PrintLog("img_log successfuly opened in constructor\n");
        else
            LOG_WRITE PrintLog("OpenFile() failed to open img_log in constructor\n");
    }

//    elements[0].data = NULL_ELEM;
    //strcpy(elements[0].data ,NULL_ELEM);
    elements[0].next = 0;
    elements[0].prev = 0;

//    elements[1].data = NULL_ELEM;
    //strcpy(elements[1].data ,NULL_ELEM);
    elements[1].next = 2;
    elements[1].prev = 0;

    for(int i = 2; i < MAX_ELEMENTS; i++){
        elements[i].next = i + 1;
        elements[i].prev = NO_PTR;
    }

    elements[MAX_ELEMENTS - 1].next = 0;
    elements[MAX_ELEMENTS - 1].prev = NO_PTR;

    LOG_WRITE PrintLog("Constructor(): elements filled\n");
    DEBUG fprintf(stderr, "Constructor(): elements filled\n");
}

int ArrList::AddElemAfter (int after_which, data_t data[])
{
    LOG_WRITE PrintLog("\nCalling AddElemAfter()\n");
    DEBUG fprintf(stderr, "\nCalling AddElemAfter()\n");

    assert(after_which > 0);
    assert(after_which < MAX_ELEMENTS);

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    //if(elements[after_which].prev == NO_PTR){
    if(!ElemExists(after_which)){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", after_which);
        LOG_WRITE PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    //if(elements[free].next == NULL_PTR){
    if(ListOwerflown()){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31mList is full, can not add any element\x1b[0m\n");
        LOG_WRITE PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

        ARR_LIST_ASSERT();
        return LIST_OVERFLOW;
    }

    //  ============================================

    int new_free = elements[free].next;
    int new_elem_pos = free;

    SUPER_DEBUG PrintVarriable(free);
    SUPER_DEBUG PrintVarriable(new_free);

    if(after_which != tail)
        elements[new_elem_pos].next = elements[after_which].next;

    elements[new_elem_pos].prev = after_which;
    //elements[new_elem_pos].data = data;
    strcpy(elements[new_elem_pos].data, data);


    // Remembering pointer to last elem in this trio
    int old_after_which_next = elements[after_which].next;

    if(after_which != tail)
        elements[old_after_which_next].prev = new_elem_pos;

    free = new_free;

    elements[after_which].next = new_elem_pos;

    //  ============================================

    if(after_which == tail)
        tail = new_elem_pos;

    n_elem++;

    SUPER_DEBUG PrintListAttributes();

    SUPER_DEBUG PrintVarriable(after_which);
    SUPER_DEBUG PrintVarriable(elements[after_which].next);
    SUPER_DEBUG PrintVarriable(elements[after_which].prev);

    SUPER_DEBUG PrintVarriable(new_elem_pos);
    SUPER_DEBUG PrintVarriable(elements[new_elem_pos].next);
    SUPER_DEBUG PrintVarriable(elements[new_elem_pos].prev);

    SUPER_DEBUG PrintVarriable(old_after_which_next);
    SUPER_DEBUG PrintVarriable(elements[old_after_which_next].next);
    SUPER_DEBUG PrintVarriable(elements[old_after_which_next].prev);

    DEBUG fprintf(stderr, "\x1b[32mAdded element:\nposition\t%d\n next\t\t%d\n prev\t\t%d\x1b[0m\n", new_elem_pos,
                                                        elements[new_elem_pos].next, elements[new_elem_pos].prev);

    LOG_WRITE PrintLog("Quiting AddElemAfter()\n");
    DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::AddElemBefore(int before_which, data_t data[])
{
    LOG_WRITE PrintLog("\nCalling AddElemBefore()\n");
    DEBUG fprintf(stderr, "\nCalling AddElemBefore()\n");

    assert(before_which > 0);
    assert(before_which < MAX_ELEMENTS);

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    //if(elements[before_which].prev == NO_PTR){
    if(!ElemExists(before_which)){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", before_which);
        LOG_WRITE PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    //if(elements[free].next == NULL_PTR){
    if(ListOwerflown()){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31mList is full, can not add any element\x1b[0m\n");
        LOG_WRITE PrintLog("Quiting AddElemBefore()\n");
        DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

        ARR_LIST_ASSERT();
        return LIST_OVERFLOW;
    }

    //  ============================================

    int new_free = elements[free].next;
    int new_elem_pos = free;

    elements[new_elem_pos].next = before_which;
    elements[new_elem_pos].prev = elements[before_which].prev;
    //elements[new_elem_pos].data = data;
    strcpy(elements[new_elem_pos].data, data);

    // Remembering pointer to last elem in this trio
    int old_before_which_prev = elements[before_which].prev;

    elements[before_which].prev = new_elem_pos;
    elements[old_before_which_prev].next = new_elem_pos;

    free = new_free;

    //DEBUG fprintf(stderr, "\x1b[32mElement added: position = %d\x1b[0m\n", new_elem_pos);

    //  ============================================

    if(before_which == head)
        head = new_elem_pos;

    n_elem++;

    SUPER_DEBUG PrintListAttributes();

    SUPER_DEBUG PrintVarriable(before_which);
    SUPER_DEBUG PrintVarriable(elements[before_which].next);
    SUPER_DEBUG PrintVarriable(elements[before_which].prev);

    SUPER_DEBUG PrintVarriable(new_elem_pos);
    SUPER_DEBUG PrintVarriable(elements[new_elem_pos].next);
    SUPER_DEBUG PrintVarriable(elements[new_elem_pos].prev);

    SUPER_DEBUG PrintVarriable(old_before_which_prev);
    SUPER_DEBUG PrintVarriable(elements[old_before_which_prev].next);
    SUPER_DEBUG PrintVarriable(elements[old_before_which_prev].prev);

    DEBUG fprintf(stderr, "\x1b[32mAdded element:\nposition\t%d\n next\t\t%d\n prev\t\t%d\x1b[0m\n", new_elem_pos,
                                                        elements[new_elem_pos].next, elements[new_elem_pos].prev);

    LOG_WRITE PrintLog("Quiting AddElemBefore()\n");
    DEBUG fprintf(stderr, "Quiting AddElemBefore()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::DelElemAfter (int after_which)
{
    LOG_WRITE PrintLog("\nCalling DelElemAfter()\n");
    DEBUG fprintf(stderr, "\nCalling DelElemAfter()\n");

    assert(after_which > 0);
    assert(after_which < MAX_ELEMENTS);

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    //if(elements[after_which].prev == NO_PTR){
    if(!ElemExists(after_which)){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", after_which);
        LOG_WRITE PrintLog("Quiting DelElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    if(after_which == tail){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31mNext element does not exist, can not delete it\x1b[0m\n");
        LOG_WRITE PrintLog("Quiting DelElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");

        ARR_LIST_ASSERT();
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
    //elements[del_elem_pos].data = NULL_ELEM;
    strcpy(elements[0].data ,NULL_ELEM);

    free = del_elem_pos;

    DEBUG fprintf(stderr, "\x1b[32mDeleted element:\nposition\t%d\n next\t\t%d\n prev\t\t%d\x1b[0m\n", del_elem_pos,
                                                        elements[del_elem_pos].next, elements[del_elem_pos].prev);

    //  ============================================

    if(del_elem_pos == tail)
        tail = after_which;

    n_elem--;

    SUPER_DEBUG PrintListAttributes();

    SUPER_DEBUG PrintVarriable(after_which);
    SUPER_DEBUG PrintVarriable(elements[after_which].next);
    SUPER_DEBUG PrintVarriable(elements[after_which].prev);

    SUPER_DEBUG PrintVarriable(del_elem_pos);
    SUPER_DEBUG PrintVarriable(elements[del_elem_pos].next);
    SUPER_DEBUG PrintVarriable(elements[del_elem_pos].prev);

    SUPER_DEBUG PrintVarriable(del_next);
    SUPER_DEBUG PrintVarriable(elements[del_next].next);
    SUPER_DEBUG PrintVarriable(elements[del_next].prev);

    LOG_WRITE PrintLog("Quiting DelElemAfter()\n");
    DEBUG fprintf(stderr, "Quiting DelElemAfter()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::DelElemBefore(int before_which)
{
    LOG_WRITE PrintLog("\nCalling DelElemBefore()\n");
    DEBUG fprintf(stderr, "\nCalling DelElemBefore()\n");

    assert(before_which > 0);
    assert(before_which < MAX_ELEMENTS);

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    //if(elements[before_which].prev == NO_PTR){
    if(!ElemExists(before_which)){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", before_which);
        LOG_WRITE PrintLog("Quiting AddElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    if(before_which == head){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31mPrevious element does not exist, can not delete it\x1b[0m\n");
        LOG_WRITE PrintLog("Quiting AddElemAfter()\n");
        DEBUG fprintf(stderr, "Quiting AddElemAfter()\n");

        ARR_LIST_ASSERT();
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
    //elements[del_elem_pos].data = NULL_ELEM;
    strcpy(elements[0].data ,NULL_ELEM);

    free = del_elem_pos;

    //  ============================================

    if(del_elem_pos == head)
        head = before_which;

    n_elem--;

    SUPER_DEBUG PrintListAttributes();

    SUPER_DEBUG PrintVarriable(before_which);
    SUPER_DEBUG PrintVarriable(elements[before_which].next);
    SUPER_DEBUG PrintVarriable(elements[before_which].prev);

    SUPER_DEBUG PrintVarriable(del_elem_pos);
    SUPER_DEBUG PrintVarriable(elements[del_elem_pos].next);
    SUPER_DEBUG PrintVarriable(elements[del_elem_pos].prev);

    SUPER_DEBUG PrintVarriable(del_prev);
    SUPER_DEBUG PrintVarriable(elements[del_prev].next);
    SUPER_DEBUG PrintVarriable(elements[del_prev].prev);

    DEBUG fprintf(stderr, "\x1b[32mDeleted element:\nposition\t%d\n next\t\t%d\n prev\t\t%d\x1b[0m\n", del_elem_pos,
                                                        elements[del_elem_pos].next, elements[del_elem_pos].prev);

    LOG_WRITE PrintLog("Quiting DelElemBefore()\n");
    DEBUG fprintf(stderr, "Quiting DelElemBefore()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::SetData(int elem_pos, data_t data[])
{
    LOG_WRITE PrintLog("\nCalling SetData()\n");
    DEBUG fprintf(stderr, "\nCalling SetData()\n");

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    if(!ElemExists(elem_pos)){
        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", elem_pos);
        LOG_WRITE PrintLog("Quiting SetData()\n");
        DEBUG fprintf(stderr, "Quiting SetData()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    //elements[elem_pos].data = data;
    strcpy(elements[0].data, data);
    DEBUG fprintf(stderr, "\x1b[32mNew data = %d\x1b[0m\n", elements[elem_pos].data);

    SUPER_DEBUG PrintVarriable(elem_pos);
    SUPER_DEBUG PrintVarriable(elements[elem_pos].data);
    SUPER_DEBUG PrintVarriable(data);

    LOG_WRITE PrintLog("Quiting SetData()\n");
    DEBUG fprintf(stderr, "Quiting SetData()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::GetElemData(int elem_pos, data_t* elem_data[])
{
    LOG_WRITE PrintLog("\nCalling GetElemData()\n");
    DEBUG fprintf(stderr, "\nCalling GetElemData()\n");

    ARR_LIST_ASSERT();

    // Check if user does not try to work with empty space
    if(!ElemExists(elem_pos)){
        elem_data = nullptr;

        PrintListAttributes();
        DEBUG fprintf(stderr, "\x1b[31m%d is not an element of the list\x1b[0m\n", elem_pos);
        LOG_WRITE PrintLog("Quiting GetElemData()\n");
        DEBUG fprintf(stderr, "Quiting GetElemData()\n");

        ARR_LIST_ASSERT();
        return ELEMENT_DOES_NOT_EXIST;
    }

    *elem_data = elements[elem_pos].data;
    DEBUG fprintf(stderr, "\x1b[32mdata = %d\x1b[0m\n", *elem_data);

    SUPER_DEBUG PrintVarriable(elem_pos);
    SUPER_DEBUG PrintVarriable(elements[elem_pos].data);
    SUPER_DEBUG PrintVarriable(*elem_data);

    LOG_WRITE PrintLog("Quiting GetElemData()\n");
    DEBUG fprintf(stderr, "Quiting GetElemData()\n");

    ARR_LIST_ASSERT();
    return SUCCESS;
}

int ArrList::GetNext(int elem_pos)
{
    return elements[elem_pos].next;
}

int ArrList::GetHead()
{
    return head;
}

int ArrList::GetTail()
{
    return tail;
}

// =========================    // Dumps

int ArrList::Dump(int err_code, const char* func)
{
    DEBUG fprintf(stderr, "\n\x1b[34m-----DUMP IN %s():-----\x1b[0m\n", func);
          fprintf(txt_log, "-----DUMP IN %s():-----\n", func);

    switch (err_code){
        case SUCCESS:
        {
            DEBUG fprintf(stderr, "\x1b[32mEVERYTHING IS OK\x1b[0m\n");
            fprintf(txt_log, "Everything is OK\n");

            PrintListAttributes();
            fprintf(txt_log, "head =\t%d\ntail =\t%d\nfree =\t%d\nn_elem =\t%d\n", head, tail, free, n_elem);
            PrintVarriable(img_log_status);
            fprintf(txt_log, "img_log_status =\t%d\n", img_log_status);
            PrintVarriable(txt_log_status);
            fprintf(txt_log, "txt_log_status =\t%d\n", txt_log_status);

            int i = head;
            while(i != tail){
                fprintf(txt_log, "i =\t%d\n", i);
                fprintf(txt_log, "elements[%d].data =\t%d\n", i, elements[i].data);
                fprintf(txt_log, "elements[%d].next =\t%d\n", i, elements[i].next);
                fprintf(txt_log, "elements[%d].prev =\t%d\n", i, elements[i].prev);

                PrintVarriable(i);
                PrintVarriable(elements[i].data);
                PrintVarriable(elements[i].next);
                PrintVarriable(elements[i].prev);

                i = elements[i].next;
            }
            fprintf(txt_log, "i =\t%d\n", i);
            fprintf(txt_log, "elements[%d].data =\t%d\n", i, elements[i].data);
            fprintf(txt_log, "elements[%d].next =\t%d\n", i, elements[i].next);
            fprintf(txt_log, "elements[%d].prev =\t%d\n", i, elements[i].prev);

            PrintVarriable(i);
            PrintVarriable(elements[i].data);
            PrintVarriable(elements[i].next);
            PrintVarriable(elements[i].prev);

            break;
        }
        case LIST_LOOPED:
        {
            DEBUG fprintf(stderr, "\x1b[31mLIST LOOPED\x1b[0m\n");
            fprintf(txt_log, "LIST LOOPED\n");

            DEBUG fprintf(stderr, "Nothing will be printed, look on the image dump. Sorry.\n");
            fprintf(txt_log, "Nothing will be printed, look on the image dump. Sorry.\n");

            break;
        }
        case CONNECTION_WRONG:
        {
            DEBUG fprintf(stderr, "\x1b[31mCONNECTION BROKEN\x1b[0m\n");
            fprintf(txt_log, "CONNECTION BROKEN\n");

            PrintListAttributes();
            fprintf(txt_log, "head =\t%d\ntail =\t%d\nfree =\t%d\nn_elem =\t%d\n", head, tail, free, n_elem);
            PrintVarriable(img_log_status);
            fprintf(txt_log, "img_log_status =\t%d\n", img_log_status);
            PrintVarriable(txt_log_status);
            fprintf(txt_log, "txt_log_status =\t%d\n", txt_log_status);

            int i = head;
            while(i != tail){
                fprintf(txt_log, "i =\t%d\n", i);
                fprintf(txt_log, "elements[%d].data =\t%d\n", i, elements[i].data);
                fprintf(txt_log, "elements[%d].next =\t%d\n", i, elements[i].next);
                fprintf(txt_log, "elements[%d].prev =\t%d\n", i, elements[i].prev);

                PrintVarriable(i);
                PrintVarriable(elements[i].data);
                PrintVarriable(elements[i].next);
                PrintVarriable(elements[i].prev);

                i = elements[i].next;
            }
            fprintf(txt_log, "i =\t%d\n", i);
            fprintf(txt_log, "elements[%d].data =\t%d\n", i, elements[i].data);
            fprintf(txt_log, "elements[%d].next =\t%d\n", i, elements[i].next);
            fprintf(txt_log, "elements[%d].prev =\t%d\n", i, elements[i].prev);

            PrintVarriable(i);
            PrintVarriable(elements[i].data);
            PrintVarriable(elements[i].next);
            PrintVarriable(elements[i].prev);

            break;
        }
    }
    DEBUG fprintf(stderr, "\n\x1b[34m-----DUMP QUITED-----\x1b[0m\n");
          fprintf(txt_log, "-----DUMP QUITED-----\n", func);

    return SUCCESS;
}

int ArrList::PrintLog(const char* info)
{
    int res = 0;
    if(txt_log_status != FILE_NOT_OPENED)
        res = fprintf(txt_log, info);
    return res;
}

int ArrList::PrintListAttributes()
{
    PrintVarriable(head);
    PrintVarriable(tail);
    PrintVarriable(free);
    PrintVarriable(n_elem);

    return 4;
}

int ArrList::WriteDotImg(FILE* img_dot_source)
{
    assert(img_dot_source != nullptr);

    LOG_WRITE PrintLog("\nCalling WriteDotImg()\n");
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

        SUPER_DEBUG PrintVarriable(i);
        SUPER_DEBUG PrintVarriable(elements[i].next);

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

    SUPER_DEBUG PrintVarriable(i);
    SUPER_DEBUG PrintVarriable(elements[i].next);

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

    LOG_WRITE PrintLog("Quiting WriteDotImg()\n");
    DEBUG fprintf(stderr, "Quiting WriteDotImg()\n");

    return i;
}

int ArrList::CompileDotImg(const char* text, const char* img)
{
    LOG_WRITE PrintLog("\nCalling CompileDotImg()\n");
    DEBUG fprintf(stderr, "\nCalling CompileDotImg()\n");

    char command[1000];
    strcpy(command, DOT1);
    strcat(command, text);
    strcat(command, DOT2);
    strcat(command, img);

    DEBUG fprintf(stderr, "Closing img_log in CompileDotImg():\n");
                 LOG_WRITE PrintLog("Closing img_log in CompileDotImg():\n");
    fclose(img_log);
    DEBUG fprintf(stderr, "\x1b[32mimg_log closed in CompileDotImg()\x1b[0m\n");
                 LOG_WRITE PrintLog("img_log closed in CompileDotImg()\n");

    DEBUG fprintf(stderr, "Command to execute in CompileDotImg(): \"%s\"\n", command);
                 LOG_WRITE PrintLog("Command to execute in CompileDotImg(): \"");
                 LOG_WRITE PrintLog(command);
                 LOG_WRITE PrintLog("\"\n");

    LOG_WRITE PrintLog("Quiting CompileDotImg()\n");
    DEBUG fprintf(stderr, "Quiting CompileDotImg()\n");
    return system(command);
}

int ArrList::CallDumpImg(const char* img)
{
    LOG_WRITE PrintLog("\nCalling CallDumpImg()\n");
    DEBUG fprintf(stderr, "\nCalling CallDumpImg()\n");

    char command[1000];
    strcpy(command, OPEN);
    strcat(command, img);

    int res = system(command);
    DEBUG fprintf(stderr, "Command to execute in CallDumpImg(): |%s|\n", command);
                 LOG_WRITE PrintLog("Command to execute in CallDumpImg(): \"");
                 LOG_WRITE PrintLog(command);
                 LOG_WRITE PrintLog("\"\n");

    DEBUG fprintf(stderr, "Opening img_log in CallDumpImg():\n");
                 LOG_WRITE PrintLog("Opening img_log in CallDumpImg():\n");
    if(!OpenFile(&img_log, TXT_LOG_NAME, "w"))
        LOG_WRITE PrintLog("img_log opened in CallDumpImg()\n");
    else
        LOG_WRITE PrintLog("OpenFile() failed to open img_log in CallDumpImg()\n");

    LOG_WRITE PrintLog("Quiting CallDumpImg()\n");
    DEBUG fprintf(stderr, "Quiting CallDumpImg()\n");
    return res;
}

int ArrList::CallImg()
{
    WriteDotImg(img_log);
    CompileDotImg(IMG_LOG_SOURCE_NAME, IMG_LOG_RESULT_NAME);
    return CallDumpImg(IMG_LOG_RESULT_NAME);
}

// =========================    // Slow - functions

int ArrList::FindElemSlow(int logical_pos)
{
    LOG_WRITE PrintLog("\nCalling FindElemSlow()\n");
    DEBUG fprintf(stderr, "\nCalling FindElemSlow()\n");

    DEBUG fprintf(stderr, "\n\n\x1b[31m\tThis List's standart strongly do not recommend to use \n\
    \tthis function as it kills the main idea and advantages of the List\x1b[0m\n\n");

    int i = head;
    while(i != tail){
        if(i == logical_pos){
            DEBUG fprintf(stderr, "\x1b[32mReturned element: position = %d\n\x1b[0m\n", i);
            LOG_WRITE PrintLog("Quiting FindElemSlow()\n");
            DEBUG fprintf(stderr, "Quiting FindElemSlow()\n");
            return i;
        }
        i = elements[i].next;
    }

    DEBUG fprintf(stderr, "\x1b[31mNo element has been found\n\x1b[0m\n", i);

    LOG_WRITE PrintLog("Quiting FindElemSlow()\n");
    DEBUG fprintf(stderr, "Quiting FindElemSlow()\n");

    return ELEMENT_DOES_NOT_EXIST;
}


