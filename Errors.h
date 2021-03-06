#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

enum Errors {
    ELEMENT_DOES_NOT_EXIST = -1,
    SUCCESS = 0,

    FILE_NOT_OPENED,
    LIST_OVERFLOW,
    ELEMENT_IS_EMPTY,

    LIST_LOOPED,
    CONNECTION_WRONG
};

#endif // ERRORS_H_INCLUDED
