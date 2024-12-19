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
    NEW_LINE   = 1 << 6,
};

union TokenValue {
    double double_value;
    char*  text_pointer;
};

struct Token {
    TokenValue value;
    TokenType  type;
    int        line          = 0;
    int        index_in_line = 0;
};

bool IsAlpha(char symbol);
TYPE_OF_ERROR TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size);
TYPE_OF_ERROR ScanLexeme    (char* string, Buffer<Token>* tokens, int* line_index, int* char_index);
TokenType     GetTokenType  (char* string, int* char_index);
TYPE_OF_ERROR WriteSyntaxError(char* string, int* line_index, int* char_index);
void          SkipSpaces    (const char* s, int* p);

#endif
