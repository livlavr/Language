#ifndef TOKENIZATION_H_
#define TOKENIZATION_H_

#include "Buffer.h"

enum TokenType { //TODO delete useless
    CONST      = 0,
    CYRILLIC_W = 1,
    ENGLISH_W  = 1 << 1,
    OPERATION  = 1 << 2,
    BRACKET    = 1 << 3,
    SEPARATOR  = 1 << 4,
    OPERATOR   = 1 << 5,
    TYPE_NAME  = 1 << 6,
    KEYWORD    = 1 << 7,
    UNDEFINED  = 1 << 8,
};

union TokenValue {
    int    int_value;
    char*  text_pointer;
    int    keyword_index;
};

struct Token {
    TokenValue value         = {.text_pointer = NULL};
    TokenType  type          = UNDEFINED;
    int        line          = -1;
    int        index_in_line = -1;
};

TYPE_OF_ERROR TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size);
TYPE_OF_ERROR PrintLine     (char* string, int char_index);

#endif
