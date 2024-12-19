#include <stdio.h>
#include <ctype.h>

#include "custom_asserts.h"
#include "Tokenization.h"
#include "debug_macros.h"

#define _line buffer->data[line_index]
#define _symbol string[*char_index]

TYPE_OF_ERROR TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size) {
    check_expression(buffer, POINTER_IS_NULL);
    check_expression(tokens, POINTER_IS_NULL);

    tokens->data = (Token*)calloc(size_t(tokens_size), sizeof(Token));
    warning(tokens, CALLOC_ERROR);

    int char_index = 0;
    for(int line_index = 0; line_index < buffer->size; line_index++) {
        char_index = 0;
        while(_line[char_index] != '\n' && _line[char_index] != EOF) {
            ScanLexeme(_line, tokens, &line_index, &char_index);
        }
    }

    return SUCCESS;
}

TYPE_OF_ERROR ScanLexeme(char* string, Buffer<Token>* tokens, int* line_index, int* char_index) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    SkipSpaces(string, char_index);
    double number = 0;
    int    number_size = 0;
    switch(GetTokenType(string, char_index)) {
        case CONST:
            sscanf(&(_symbol), "%lf%n", &number, &number_size);
            tokens->data[tokens->size].type  = CONST;
            tokens->data[tokens->size].value.double_value = number;
            tokens->data[tokens->size].index_in_line = *char_index;
            tokens->data[tokens->size].line          = *line_index;
            (*char_index) += number_size;
            (tokens->size)++;
            printf("CONST\n");
            break;
        case ENGLISH_W:
            printf("ENGLISH_W\n");
            break;
        case CYRILLIC_W:
            printf("CYRILLIC_W\n");
            break;
        case BRACKET:
            printf("BRACKET\n");
            break;
        case OPERATION:
            printf("OPERATION\n");
            break;
        case SEPARATOR:
            printf("SEPARATOR\n");
            break;
        case NEW_LINE:
            printf("NEW_LINE\n");
            (*char_index)++;
            break;
        case UNDEFINED:
            printf("UNDEFINED\n");
            break;
        default:
            printf("default\n");
            break;
            // color_printf(RED_COLOR, BOLD, "Undefined Symbol at %d:\n", *line_index);
            // WriteSyntaxError(string, line_index, char_index);
    }

    return SUCCESS;
}

TokenType GetTokenType(char* string, int* char_index) {
    warning(string,     POINTER_IS_NULL);
    warning(char_index, POINTER_IS_NULL);

    if(isdigit(_symbol)) {
        return CONST;
    }
    if(isalpha(_symbol)) {
        return ENGLISH_W;
    }
    if(false) { //TODO
        return CYRILLIC_W;
    }
    if(_symbol == '{' || _symbol == '}' || _symbol == '[' ||
       _symbol == ']' || _symbol == '(' || _symbol == ')' ) {
        return BRACKET;
    }
    if(_symbol == '+' || _symbol == '-' || _symbol == '*' ||
       _symbol == '/' || _symbol == '=' || _symbol == '^' ||
       _symbol == '<' || _symbol == '>' || _symbol == '!' ) {
        return OPERATION;
    }
    if(_symbol == ';' || _symbol == ',' || _symbol == '.' ) {
        return SEPARATOR;
    }
    if(_symbol == '\n') {
        return NEW_LINE;
    }

    return UNDEFINED;
}

TYPE_OF_ERROR WriteSyntaxError(char* string, int* line_index, int* char_index) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "%d: %*.*s\n", *line_index, 2, 2, string);
    for(int space_number = 0; space_number < *char_index; space_number++) {
        printf(" ");
    }
    color_printf(RED_COLOR, BOLD, "^");

    return SUCCESS;
}

// TYPE_OF_ERROR TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, size_t tokens_size) {
//     check_expression(buffer, POINTER_IS_NULL);
//
//     tokens->data = (Token*)calloc(tokens_size, sizeof(Token));
//     warning(tokens, CALLOC_ERROR);
//
//     char** text = buffer->data;
//     size_t token_index     = 0;
//     size_t double_size     = 0;
//     size_t char_index      = 0;
//     double number          = 0;
//     size_t start_of_lexeme = 0;
//     // $DEBUG("%d", buffer->size);
//
//     for(size_t line_index = 0; line_index < buffer->size; line_index++) {
//         char_index = 0;
//         while(text[line_index][char_index] != '\n') {
//             if(IsAlpha(text[line_index][char_index])) {
//                 start_of_lexeme = char_index;
//                 while(isalpha(text[line_index][char_index])) {
//                     char_index++;
//                 }
//                 tokens->data[token_index].text_pointer = &(text[line_index][start_of_lexeme]);
//                 tokens->data[token_index].type         = WORD;
//                 tokens->size++;
//                 token_index++;
//             }
//             else if(isdigit(text[line_index][char_index])) {
//                 sscanf(&(text[line_index][char_index]), "%lf%n", &number, &double_size);
//                 tokens->data[token_index].text_pointer = &(text[line_index][char_index]);
//                 tokens->data[token_index].type         = NUMBER;
//                 tokens->size++;
//                 token_index++;
//                 char_index += double_size;
//             }
//             else if (text[line_index][char_index] != ' '){
//                 tokens->data[token_index].text_pointer = &(text[line_index][char_index]);
//                 tokens->data[token_index].type         = OPERATION;
//                 tokens->size++;
//                 token_index++;
//                 char_index++;
//             }
//             else
//                 char_index++;
//         }
//     }
//
//     return SUCCESS;
// }

void SkipSpaces(const char* s, int* p) {
    while(s[*p] == ' ') {
        (*p)++;
    };
}
