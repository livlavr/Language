#include <stdio.h>
#include <ctype.h>
#include <cmath>

#include "Tokenization.h"
#include "BufferSpecializations.h"
#include "debug_macros.h"

int main() {
    Buffer<char>   code   = {};
    Buffer<char*>  lines  = {};
    Buffer<Token> tokens  = {};
    ReadFile(&code, "tests/test.txt");
    // $DEBUG("%d", code.size);
    GetLinePointersFromFile(&lines, &code);

    // printf("%s", code.data);

    // $DEBUG("%d", lines.size);
    // for(int i = 0; i < lines.size; i++) {
    //     printf(">%s\n", lines.data[i]);
    // }

    TokenizeBuffer(&lines, &tokens, code.capacity);

    $DEBUG("%d", tokens.size);
    for(int i = 0; i < tokens.size; i++) {
        if(tokens.data[i].type == CONST) {
            printf("< %d >", tokens.data[i].type);
            printf("%d\n", tokens.data[i].value.int_value);
        }
        else if(tokens.data[i].type == CYRILLIC_W || tokens.data[i].type == ENGLISH_W) {
            printf("< %d >", tokens.data[i].type);
            PrintLine(tokens.data[i].value.text_pointer, -1);
        }
        else {
            printf("< %d >", tokens.data[i].type);
            printf("%d\n", tokens.data[i].value.keyword_index);
        }
    }

    BufferDtor(&code);
    BufferDtor(&lines);
    BufferDtor(&tokens);
}
