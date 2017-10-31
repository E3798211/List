#include <iostream>

#include "List.h"
#include "HashTest.h"

//#include <sys/elf.h>
//#include <sys/procfs.h>

int main()
{

    char* words_in_line = FileRead(WORDS);
    if(words_in_line == nullptr){
        printf("words_in_line = nullptr.\n");
        return FILE_NOT_OPENED;
    }

    int n = LinesCount(words_in_line);
    Line* words = Parse(&words_in_line, n);

    // Now we have an array with all words. Lets test hash!

    const int hash_test_array_size = 300;
    //ArrList map[hash_test_array_size];

    ArrList* map = new ArrList [hash_test_array_size];

    int i = 0;
    while(i < n){
        int hash = Hash_0(words[i].beg);
        hash = hash % hash_test_array_size;

        /*
        cout << "hash = " << hash << endl;
        cout << "n_el = " << map[hash].n_elem << endl;
        cout << "tail = " << map[hash].GetTail() << endl;
        cout << "word = " << words[i].beg;
        */


        if(map[hash].n_elem > 1){
            if(!SuchWordAlreadyCounted(words[i].beg, map[hash]))
                map[hash].AddElemAfter(map[hash].GetTail(), words[i].beg);
        }
        else{
            map[hash].AddElemAfter(map[hash].GetTail(), words[i].beg);
        }
        i++;
    }


    cout << "ho\n";
    for(int i = 0; i < hash_test_array_size; i++){
        printf("elem num = %d\n", map[i].n_elem - 1);
    }


}

