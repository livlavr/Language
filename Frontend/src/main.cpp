#include <stdio.h>
#include <ctype.h>

#include "Tokenization.h"
#include "debug_macros.h"

int main() {
    Buffer<char>   code   = {};
    Buffer<char*>  lines  = {};
    Buffer<Token> tokens  = {};
    ReadFile(&code, "Code-examples/test.txt");
    $DEBUG("%d", code.size);
    GetLinePointersFromFile(&lines, "Code-examples/test.txt");

    // $DEBUG("%d", lines.size);
    // for(int i = 0; i < lines.size; i++) {
    //     printf(">%s\n", lines.data[i]);
    // }

    TokenizeBuffer(&lines, &tokens, code.size);
//
    $DEBUG("%d", tokens.size);
    for(int i = 0; i < tokens.size; i++) {
        printf("%lf\n", tokens.data[i].value.double_value);
    }

    BufferDtor(&code);
    BufferDtor(&lines);
}
