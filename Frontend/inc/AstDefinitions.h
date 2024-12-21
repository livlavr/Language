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

enum class KeywordType {
    UNDEFINED = 0,

    #define KEYWORD(NAME, NUMBER, TEXT_RECORD, TYPE, ...) NAME = NUMBER,

    #include "Keywords.def"

    #undef KEYWORD
};


enum class AstNodeType{
    CONSTANT            = 1,
    IDENTIFIER          = 2,
    KEYWORD             = 3,
    FUNCTION_DEFINITION = 4,
    PARAMETERS          = 5,
    VAR_DECLARATION     = 6,
    FUNCTION_CALL       = 7,
};

union AstNodeValue{
    int int_value;
    int id;
};

struct AstNode {
    AstNodeType  type;
    AstNodeValue data = {.int_value = 0};
    int          scope = -1;
};

TreeNode<AstNode>* CreateAstNode(AstNode ast_value,
    TreeNode<AstNode>* left, TreeNode<AstNode>* right);

#define Keyword(keyword_id, left, right)                                           CreateAstNode({.type = AstNodeType::KEYWORD,             .data = {.id = keyword_id   }, .scope = context->current_scope}, left,          right                    )
#define Constant(number)                                                           CreateAstNode({.type = AstNodeType::CONSTANT,            .data = {.int_value = number}, .scope = context->current_scope}, NULL,          NULL                     )
#define Identifier(identifier_id)                                                  CreateAstNode({.type = AstNodeType::IDENTIFIER,          .data = {.id = identifier_id}, .scope = context->current_scope}, NULL,          NULL                     )
#define Parameters(GetParameters, function_body)                                   CreateAstNode({.type = AstNodeType::PARAMETERS,          .data = {.id = -1           }, .scope = context->current_scope}, GetParameters, function_body            )
#define FunctionCall(GetArgs, identifier_id)                                       CreateAstNode({.type = AstNodeType::FUNCTION_CALL,       .data = {.id = -1           }, .scope = context->current_scope}, GetArgs,       Identifier(identifier_id))
#define VariableDeclaration(identifier_id, type_name, identifier_or_GetExpression) CreateAstNode({.type = AstNodeType::VAR_DECLARATION,     .data = {.id = identifier_id}, .scope = context->current_scope}, type_name,     identifier_or_expression )
#define FunctionDefinition(identifier_id, type_name, GetParameters)                CreateAstNode({.type = AstNodeType::FUNCTION_DEFINITION, .data = {.id = identifier_id}, .scope = context->current_scope}, type_name,     GetParameters            )

#endif
