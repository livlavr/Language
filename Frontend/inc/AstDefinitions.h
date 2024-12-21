#ifndef AST_DEFINITIONS_H_
#define AST_DEFINITIONS_H_

#include "tree.h"

//| Номер типа | Тип узла             | Содержание узла                                                                  |
//|------------|----------------------|----------------------------------------------------------------------------------|
//| 1          | `Constant`           | Число в виде десятичной дроби                                                    |
//| 2          | `Identifier`         | Индекс идентификатора в общей таблице имен                                       |
//| 3          | `Keyword`            | Номер ключевого слова                                                            |
//| 4          | `FunctionDefinition` | Индекс идентификатора функции, задаваемой данным узлом                           |
//| 5          | `Parameters`         | Нет хранимой величины                                                            |
//| 6          | `VarDeclaration`     | Идентификатор создаваемой переменной                                             |
//| 7          | `Call`               | Нет хранимой величины                                                            |

/*
union NodeContent {
    double  number = NAN;
    size_t  nameTableIndex;
    Keyword keyword;
};

struct AstNode {
    NodeType    type    = NodeType::CONSTANT;
    NodeContent content = {.number = NAN};
    int         line    = 0;
    char       *file    = nullptr;
};
*/

enum Operations {
    UNDEF      = -1,
    IF         = 11,
    WHILE      = 12,
    ASSIGN     = 13,
    SIN        = 21,
    COS        = 22,
    FLOOR      = 23,
    ADD        = 24,
    SUB        = 25,
    MUL        = 26,
    DIV        = 27,
    SQRT       = 28,
    EQUAL      = 31,
    LESS       = 32,
    MORE       = 33,
    LEQ        = 34,
    GEQ        = 35,
    NOT_EQUAL  = 36,
    AND        = 37,
    OR         = 38,
    NOT        = 39,
    SEP        = 41,
    PARAMETERS = 42,
    CONST      = 51,
    IN         = 61,
    OUT        = 62,
    RETURN     = 71,
    BREAK      = 72,
    CONTINUE   = 73,
    ABORT      = 74,
};

enum AstNodeType{
    KEYWORD             = 0,
    CONSTANT            = 1,
    IDENTIFIER          = 1 << 1,
    PARAMETERS          = 1 << 2,
    FUNCTION_CALL       = 1 << 3,
    VAR_DECLARATION     = 1 << 4,
    FUNCTION_DEFINITION = 1 << 5,
};

union AstNodeValue{
    double double_value;
    int    identifier;
};

struct AstNode {
    AstNodeType  type;
    AstNodeValue data = {.double_value = 0};
    int          scope = -1;
};

TreeNode<AstNode>* CreateAstNode(AstNode ast_value,
    TreeNode<AstNode>* left, TreeNode<AstNode>* right);

#define Keyword(scope, id, left, right)        CreateAstNode({.type = KEYWORD,    .data = {.number = id},           .scope = scope}, left, right)
#define Constant(scope, number)                CreateAstNode({.type = CONSTANT,   .data = {.double_value = number}, .scope = scope}, NULL, NULL)
#define Identifier(scope, id)                  CreateAstNode({.type = IDENTIFIER, .data = {.number = id},           .scope = scope}, NULL, NULL)
#define Parameters(scope, left, right)         Keyword(scope, PARAMETERS, left, right)
#define FunctionCall(scope, left, right)       Keyword(scope, FUNCTION_CALL, left, right)
#define VarDeclaration(scope, left, right)     Keyword(scope, VAR_DECLARATION, left, right)
#define FunctionDefinition(scope, left, right) Keyword(scope, FUNCTION_DEFINITION, left, right)

#endif
