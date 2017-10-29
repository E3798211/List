#include "List.h"

int main()
{
    ArrList a;

    a.AddElemAfter(a.tail, 1);
    a.AddElemAfter(a.tail, 2);
    a.AddElemAfter(a.tail, 3);
    a.AddElemAfter(a.tail, 4);
    a.AddElemAfter(a.tail, 5);
    a.AddElemAfter(a.tail, 6);
    a.AddElemAfter(a.tail, 7);
    //a.DelElemAfter(1);
    //a.DelElemBefore(1);

    /*
    a.WriteDotImg(a.img_log);
    a.CompileDotImg(IMG_LOG_SOURCE_NAME, IMG_LOG_RESULT_NAME);
    a.CallDumpImg(IMG_LOG_RESULT_NAME);
    */
    a.CallImg();
}
