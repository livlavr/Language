#include <stdio.h>
#include <ctype.h>

#include "Tokenization.h"
#include "debug_macros.h"

int main() {
    Buffer<char>   code   = {};
    Buffer<char*>  lines  = {};
    Buffer<Token> tokens  = {};
    ReadFile(&code, "Code-examples/test.txt");
    // $DEBUG("%d", code.size);
    GetLinePointersFromFile(&lines, &code);

    // printf("%s", code.data);

    // $DEBUG("%d", lines.size);
    // for(int i = 0; i < lines.size; i++) {
    //     printf(">%s\n", lines.data[i]);
    // }

    TokenizeBuffer(&lines, &tokens, code.size);

    $DEBUG("%d", tokens.size);
    for(int i = 0; i < tokens.size; i++) {
        if(tokens.data[i].type == CONST) {
            printf("%lf\n", tokens.data[i].value.double_value);
        }
        else {
            PrintLine(tokens.data[i].value.text_pointer);
        }
    }

    BufferDtor(&code);
    BufferDtor(&lines);
}
