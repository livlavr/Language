#ifndef OPERATIONS_DSL_H_
#define OPERATIONS_DSL_H_

#include "AstDefinitions.h"

#define  Num(amount     ) CreateAstNode(AstNode {.type = AstNodeType::CONSTANT,.data = {.int_value = amount     }, .scope = context->current_scope}, NULL, NULL)
#define  Add(left, right) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::ADD   }, .scope = context->current_scope}, left, right)
#define  Sub(left, right) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::SUB   }, .scope = context->current_scope}, left, right)
#define  Mul(left, right) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::MUL   }, .scope = context->current_scope}, left, right)
#define  Div(left, right) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::DIV   }, .scope = context->current_scope}, left, right)
#define  Sqrt(left      ) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::SQRT  }, .scope = context->current_scope}, left, NULL)
#define  Sin(left       ) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::SIN   }, .scope = context->current_scope}, left, NULL)
#define  Cos(left       ) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::COS   }, .scope = context->current_scope}, left, NULL)
#define  Floor(left     ) CreateAstNode(AstNode {.type = AstNodeType::KEYWORD, .data = {.id = (int)KeywordType::FLOOR }, .scope = context->current_scope}, left, NULL)

#endif
