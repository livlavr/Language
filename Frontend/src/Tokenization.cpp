#include <stdio.h>
#include <ctype.h>
#include <clocale>

#include "custom_asserts.h"
#include "Tokenization.h"
#include "debug_macros.h"

#define _line   buffer->data[line_index]
#define _symbol string[*char_index]

#define _SetRedConsoleColor()                                  \
    printf("\033[31m\033[1m")

#define _CreateToken(value, type)                              \
    CreateToken(tokens, value, string, line_index, char_index, type)

#define _ScanDoubleValue()                                     \
    sscanf(&(_symbol), "%lf%n", &number, &number_size);        \
    _CreateToken(TokenValue {.double_value = number}, CONST);  \
    (*char_index) += number_size;

#define _SkipEnglishSymbols()                                  \
    while(isalpha(_symbol) || _symbol == '_') {                \
        (*char_index)++;                                       \
    }                                                          \

#define _SkipRussianSymbols()                                  \
    while(IsCyrillic(&(_symbol)) || _symbol == '_') {       \
        if(IsCyrillic(&(_symbol))) {                        \
            (*char_index) += 2;                                \
        }                                                      \
        else if(_symbol == '_') {                              \
            (*char_index) += 1;                                \
        }                                                      \
    }

static TYPE_OF_ERROR ScanLexeme          (char* string, Buffer<Token>* tokens, int* line_index, int* char_index);
static TYPE_OF_ERROR CreateToken         (Buffer<Token>* tokens, TokenValue value, char* string, int* line_index, int* char_index, TokenType type);
static TokenType     GetTokenType        (char* string, int* char_index                                        );
static TYPE_OF_ERROR SkipSpaces          (const char* s, int* p                                                );
static uint32_t      IsCyrillic          (const char *s                                                        );
static TYPE_OF_ERROR WriteSyntaxError    (char* string, int* line_index, int* char_index                       );

TYPE_OF_ERROR        TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size) {
    check_expression(buffer, POINTER_IS_NULL);
    check_expression(tokens, POINTER_IS_NULL);

    setlocale (LC_ALL, "en_US.utf8");

    tokens->data = (Token*)calloc((size_t)tokens_size, sizeof(Token));
    warning(tokens->data, CALLOC_ERROR);

    int char_index = 0;
    for(int line_index = 0; line_index < buffer->size; line_index++) {
        char_index = 0;
        while(_line[char_index] != '\n' && _line[char_index] != EOF) {
            ScanLexeme(_line, tokens, &line_index, &char_index);
        }
    }

    tokens->data = (Token*)realloc(tokens->data, ((size_t)(tokens->size + 1))*sizeof(Token));

    return SUCCESS;
}

static TYPE_OF_ERROR ScanLexeme(char* string, Buffer<Token>* tokens, int* line_index, int* char_index) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    SkipSpaces(string, char_index);
    double number      = 0;
    int    number_size = 0;
    switch(GetTokenType(string, char_index)) {
        case CONST:
            _ScanDoubleValue();
            break;
        case ENGLISH_W:
            _CreateToken(TokenValue {.text_pointer = &(_symbol)}, ENGLISH_W);
            _SkipEnglishSymbols();
            break;
        case CYRILLIC_W:
            _CreateToken(TokenValue {.text_pointer = &(_symbol)}, CYRILLIC_W);
            _SkipRussianSymbols();
            break;
        case BRACKET:
            _CreateToken(TokenValue {.text_pointer = &(_symbol)}, BRACKET);
            (*char_index)++;
            break;
        case OPERATION:
            _CreateToken(TokenValue {.text_pointer = &(_symbol)}, OPERATION);
            (*char_index)++;
            break;
        case SEPARATOR:
            _CreateToken(TokenValue {.text_pointer = &(_symbol)}, SEPARATOR);
            (*char_index)++;
            break;
        case UNDEFINED:
        default:
            color_printf(RED_COLOR, BOLD, "Undefined Symbol at %d:\n", (*line_index + 1));
            WriteSyntaxError(string, line_index, char_index);
            exit(0);
    }

    return SUCCESS;
}

static TokenType GetTokenType(char* string, int* char_index) {
    warning(string,     POINTER_IS_NULL);
    warning(char_index, POINTER_IS_NULL);

    if(isdigit(_symbol)) {
        return CONST;
    }
    if(isalpha(_symbol)) {
        return ENGLISH_W;
    }
    if(IsCyrillic(&(_symbol))) {
        return CYRILLIC_W;
    }
    if((_symbol == '{' || _symbol == '}' || _symbol == '[' ||
        _symbol == ']' || _symbol == '(' || _symbol == ')' ||
        _symbol == '\''|| _symbol == '\"'|| _symbol == '\\')) {
        return BRACKET;
    }
    if(_symbol == '+' || _symbol == '-' || _symbol == '*' ||
       _symbol == '/' || _symbol == '=' || _symbol == '^' ||
       _symbol == '<' || _symbol == '>' || _symbol == '!' ) {
        return OPERATION;
    }
    if(_symbol == ';' || _symbol == ',' || _symbol == '.' ||
       _symbol == ':') {
        return SEPARATOR;
    }

    return UNDEFINED;
}


static uint32_t IsCyrillic(const char *s)
{
    if ((*s & 0xe0) != 0xc0)
        return 0;
    if ((s[1] & 0xc0) != 0x80)
        return 0;
    uint32_t uc = ((s[0] & 0x1f) << 6) | (s[1] & 0x3f);

    if (uc < 0x400 || uc > 0x4ff)
        return 0;
    if ((uc < 0x410 || uc > 0x44f) && !(uc == 0x401 || uc == 0x451))
        return 0;

    return uc;
}

static TYPE_OF_ERROR WriteSyntaxError(char* string, int* line_index, int* char_index) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    _SetRedConsoleColor();
    PrintLine(string);
    for(int space_number = 0; space_number < *char_index; space_number++) {
        printf(" ");
    }
    color_printf(RED_COLOR, BOLD, "^\n");

    return SUCCESS;
}

static TYPE_OF_ERROR CreateToken(Buffer<Token>* tokens, TokenValue value, char* string, int* line_index, int* char_index, TokenType type) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    tokens->data[tokens->size].type  = type;

    if(type == CONST) {
        tokens->data[tokens->size].value.double_value = value.double_value;
    }
    else {
        tokens->data[tokens->size].value.text_pointer = value.text_pointer;
    }

    tokens->data[tokens->size].index_in_line = *char_index;
    tokens->data[tokens->size].line          = *line_index;

    (tokens->size)++;

    return SUCCESS;
}

TYPE_OF_ERROR PrintLine(char* string) {
    check_expression(string, POINTER_IS_NULL);

    int printed_index = 0;
    while(string[printed_index] != '\n') {
        putchar(string[printed_index]);
        printed_index++;
    }
    putchar('\n');

    return SUCCESS;
}

static TYPE_OF_ERROR SkipSpaces(const char* string, int* index) {
    check_expression(string, POINTER_IS_NULL);
    check_expression(index, POINTER_IS_NULL);

    while(string[*index] == ' ') {
        (*index)++;
    };

    return SUCCESS;
}
