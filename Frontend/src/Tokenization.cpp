#include <stdio.h>
#include <ctype.h>
#include <clocale>

#include "custom_asserts.h"
#include "Tokenization.h"
#include "debug_macros.h"

#define _line   buffer->data[line_index]
#define _symbol string[*char_index]

#define _SetRedConsoleColor()     \
    printf("\033[31m\033[1m")

#define _CreateToken(value, type)\
    CreateToken(tokens, value, string, line_index, char_index, type)

#define _ScanDoubleValue()                                     \
    sscanf(&(_symbol), "%lf%n", &number, &number_size);        \
    _CreateToken(TokenValue {.double_value = number}, CONST);  \
    (*char_index) += number_size;

#define _SkipEnglishSymbols()                                  \
    while(isalpha(_symbol)) {                                  \
        (*char_index)++;                                       \
    }                                                          \

#define _SkipRussianSymbols()                                  \
    while(IsCyrillic(&(_symbol), 1)) {                         \
        (*char_index) += 2;                                    \
    }

static TYPE_OF_ERROR ScanLexeme          (char* string, Buffer<Token>* tokens, int* line_index, int* char_index);
static TYPE_OF_ERROR CreateToken         (Buffer<Token>* tokens, TokenValue value, char* string, int* line_index, int* char_index, TokenType type);
static TokenType     GetTokenType        (char* string, int* char_index                                        );
static void          SkipSpaces          (const char* s, int* p                                                );
static int           IsCyrillic          (const char *s, int only_rus);
static TYPE_OF_ERROR WriteSyntaxError    (char* string, int* line_index, int* char_index                       );
TYPE_OF_ERROR        TokenizeBuffer(Buffer<char*>* buffer, Buffer<Token>* tokens, int tokens_size) {
    check_expression(buffer, POINTER_IS_NULL);
    check_expression(tokens, POINTER_IS_NULL);

    setlocale (LC_ALL, "en_US.utf8");

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

static TYPE_OF_ERROR ScanLexeme(char* string, Buffer<Token>* tokens, int* line_index, int* char_index) {
    check_expression(string,     POINTER_IS_NULL);
    check_expression(line_index, POINTER_IS_NULL);
    check_expression(char_index, POINTER_IS_NULL);

    SkipSpaces(string, char_index);
    double number = 0;
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
        case NEW_LINE:
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
    if(IsCyrillic(&(_symbol), 1)) {
        return CYRILLIC_W;
    }
    if(_symbol == '{' || _symbol == '}' || _symbol == '[' ||
       _symbol == ']' || _symbol == '(' || _symbol == ')' ||
       _symbol == '\''|| _symbol == '\"'|| _symbol == '\\' ) {
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


static int IsCyrillic(const char *s, int only_rus)
{
  if ((*s & 0xe0) != 0xc0)
    return 0;
  if ((s[1] & 0xc0) != 0x80)
    return 0;
  uint32_t uc = ((s[0] & 0x1f) << 6) | (s[1] & 0x3f); // 5 bits `s[0]` and 6 bits `s[1]`

  if (uc < 0x400 || uc > 0x4ff)
    return 0; // not cyrillic
  if (only_rus)
    if ((uc < 0x410 || uc > 0x44f) && // А - Я; а - я
        !(uc == 0x401 || // Ё
          uc == 0x451)) // ё
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

void PrintLine(char* string) {
    int printed_index = 0;
    while(string[printed_index] != '\n') {
        putchar(string[printed_index]);
        printed_index++;
    }
    putchar('\n');
}

void SkipSpaces(const char* s, int* p) {
    while(s[*p] == ' ') {
        (*p)++;
    };
}
