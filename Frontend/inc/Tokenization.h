#ifndef TOKENIZATION_H_
#define TOKENIZATION_H_

#include "Buffer.h"

enum TokenType {
    CONST      = 0,
    CYRILLIC_W = 1,
    ENGLISH_W  = 1 << 1,
    OPERATION  = 1 << 2,
    BRACKET    = 1 << 3,
    SEPARATOR  = 1 << 4,
    UNDEFINED  = 1 << 5,
};

union TokenValue {
    double double_value;
    char*  text_pointer;
};

struct Token {
    TokenValue value = {.text_pointer = NULL};
    TokenType  type;
    int        line          = 0;
    int        index_in_line = 0;
};

TYPE_OF_ERROR TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size);
TYPE_OF_ERROR PrintLine     (char* string);

#endif
