#ifndef HASHTEST_H_INCLUDED
#define HASHTEST_H_INCLUDED

#include <cstring>

enum WordErrors {
    WORD_EXISTS
};



const char POEM[]  = "poem.txt";
const char WORDS[] = "words.txt";


const int SORRY   = -1;

using namespace std;

struct Line{
    int lengh = 0;
    char* beg = nullptr;
};


/// Reads file and returns all lines.
/**
    \param file_name Name of the file to read.
    \warning In case of mistake returns nullptr.
*/
char* FileRead(const char* file_name);

/// Prints poem.
/**
    \warning Overoaded

    \param [in] lines_positions Pointers to the positions of lines.
    \param [in] label Your comment.
*/
void Print(Line* lines_positions, char* label = "Array");

/// Counts amount of lines in poem.
/**
    \param [in] line_to_parse Poem written in one line.
*/
int LinesCount(char* line_to_parse);

/// Parses line.
/**
    \param [in] line_to_parse Whole poem.
    \param [in] n_lines Amount of lines in a poem
*/
Line* Parse(char* line_to_parse, int n_lines);

//================================================================

/*
const char* file_name = (argc > 1)? argv[1] : POEM;

    //Reading from file
    char* poem_in_line = FileRead(file_name);
    //If nothing hive been read
    if(poem_in_line == nullptr)
        return SORRY;

    int n_lines = LinesCount(poem_in_line);
    Line* lines_positions = Parse(poem_in_line, n_lines);
*/

//================================================================

char* FileRead(const char* file_name)
{
    FILE *input = fopen(file_name, "r");
    if(input == nullptr){
        /*DEBUG*/ cout << "File not found!" << endl;
        return nullptr;
    }

    if(fseek(input, 0, SEEK_END)){
        cout << "Can not set last position in " << file_name << endl;
        return nullptr;
    }

    int file_size = ftell(input);
    if(file_size == EOF){
        cout << "Can not get pointer's position in " << file_name << endl;
        return nullptr;
    }

    char* poem_in_line = nullptr;
    try{
        poem_in_line = new char [file_size];
    }
    catch(const bad_alloc& ex){
        //cout << ERR_WHERE << ". Cannot allocate " << file_size << " bytes." << endl;
        return nullptr;
    }

    rewind(input);
    int n_chars = fread(poem_in_line, 1, file_size, input);

    fclose(input);
    return poem_in_line;
}

int LinesCount(char* line_to_parse)
{
    int n_lines = 0;
    int pos_in_line = 0;
    while(line_to_parse[pos_in_line] != '\0'){
        if(line_to_parse[pos_in_line] == '\n' || line_to_parse[pos_in_line] == ' ')
            n_lines++;
        pos_in_line++;
    }
    return n_lines;
}

Line* Parse(char** line_to_parse, int n_lines)
{
    //Exceptions
    assert((*line_to_parse) != nullptr);

    //int n_lines = LinesCount(line_to_parse);

    //Creating array with lines' coordinates
    Line* lines_positions = nullptr;
    try{
        lines_positions = new Line [n_lines + 1];
    }
    catch(const bad_alloc& ex){
        //cout << ERR_WHERE << ". Cannot allocate " << n_lines + 1 << " bytes." << endl;
        return nullptr;
    }

    //First line starts immidiately
    lines_positions[0].beg = (*line_to_parse);

    //Runnnig through the line_to_parse
    int pos_in_line = 0;
    int line_beg_num = 1;
    while((*line_to_parse)[pos_in_line] != '\0'){
        if((*line_to_parse)[pos_in_line] == '\n' || (*line_to_parse)[pos_in_line] == ' '){
            //Remembering position and going for the next line
            lines_positions[line_beg_num].beg = (*line_to_parse) + pos_in_line + 1;
            lines_positions[line_beg_num - 1].lengh = lines_positions[line_beg_num].beg -
                                                      lines_positions[line_beg_num - 1].beg - 1;
            //Ending line
            (*line_to_parse)[pos_in_line] = '\0';
            line_beg_num++;
        }
        pos_in_line++;
    }
    //Last one has wrong lengh
    lines_positions[n_lines - 1].lengh = lines_positions[n_lines].beg - lines_positions[n_lines - 1].beg - 1;
    //Array with positions of lines ends with (nullptr) (used as terminator)
    lines_positions[n_lines].beg = nullptr;

    return lines_positions;
}

void Print(Line* lines_positions, char* label)
{
    //Exceptions
    assert(lines_positions != nullptr);
    assert(label != nullptr);

    cout << "  !" << label << endl;
    int i = 0;
    while(lines_positions[i].beg != nullptr){
        cout << lines_positions[i].beg << endl;
        i++;
    }
}








unsigned int Hash_1(const char* str)
{
    return 1;
}

unsigned int Hash_0(const char* str)
{
    return str[0];
}

unsigned int Hash_l(const char* str)
{
    return strlen(str);
}

unsigned int Hash_s(const char* str)
{
    unsigned int sum = 0;

    int i = 0;
    while(str[i] != '\0')
        sum += str[i++];

    return sum;
}

unsigned int Hash_GNU(const char* str)
{
    unsigned int hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

bool SuchWordAlreadyCounted(char* word, ArrList list)
{
    int i = list.GetHead();
    data_t* data = new char [100];

    while(i != list.GetTail()){
        list.GetElemData(i, &data);

        if(!strcmp(word, data))
            return true;

        i = list.GetNext(i);
    }
    if(!strcmp(word, data))
        return true;

    return false;
}


#endif // HASHTEST_H_INCLUDED
