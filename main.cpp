#include "List.h"

int main()
{
    ArrList a;

    for(int i = 0; i < 10; i++)
        a.AddElemBefore(a.GetTail(), 1);

    //a.elements[4].prev = 7;

    a.AddElemAfter(2, 4);

    a.FindElemSlow(3);

    a.SetData(3, 100);

    data_t daaaata = 0;
    a.GetElemData(3, &daaaata);

    a.ArrListOk();

    a.CallImg();
}
