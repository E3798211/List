#include "List.h"

int main()
{
    ArrList a;

    /*
    a.AddElemAfter(a.tail, 1);
    a.AddElemAfter(a.tail, 2);
    a.AddElemAfter(a.tail, 3);
    a.AddElemAfter(a.tail, 4);
    a.AddElemAfter(a.tail, 5);
    a.AddElemAfter(a.tail, 6);
    a.AddElemAfter(a.tail, 7);

    a.AddElemBefore(a.head, 1);
    a.AddElemBefore(a.head, 2);
    a.AddElemBefore(a.head, 3);
    a.AddElemBefore(a.head, 4);
    a.AddElemBefore(a.head, 5);
    a.AddElemBefore(a.head, 6);
    a.AddElemBefore(a.head, 7);
    */
    for(int i = 0; i < 10; i++)
        a.AddElemBefore(a.tail, 1);
    for(int i = 8; i > 3; i--)
        a.DelElemBefore(i);

    //a.elements[2].prev = 7;
    //a.DelElemAfter(1);
    //a.DelElemBefore(1);

    /*
    a.WriteDotImg(a.img_log);
    a.CompileDotImg(IMG_LOG_SOURCE_NAME, IMG_LOG_RESULT_NAME);
    a.CallDumpImg(IMG_LOG_RESULT_NAME);
    */
    a.CallImg();
}
