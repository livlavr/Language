#include <stdio.h>
#include <string.h>
// #define NDEBUG

#include "tree.h"
#include "AstDefinitions.h"
#include "Tokenization.h"
#include "BufferSpecializations.h"
#include "RecursiveDescent.h"
#include "OperationsDSL.h"
#include "debug_macros.h"

//_tokens->data[_current_token].value.text_pointer
#define _current_token        context->current_token
#define _tokens               context->tokens
#define _current_name_id      context->name_table->size - 1
#define _current_symbol       _tokens->data[_current_token].value.text_pointer[0]
#define _current_value        _tokens->data[_current_token].value
#define _current_data         _tokens->data[_current_token]
#define _current_pointer      _tokens->data[_current_token].value.text_pointer
#define IsWord()              _current_data.type == ENGLISH_W || _current_data.type == CYRILLIC_W
#define IsLBracket()          _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::LBRACKET
#define IsRBracket()          _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::RBRACKET
#define IsBlockOpen()         _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::BLOCK_OPEN
#define IsBlockClose()        _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::BLOCK_CLOSE
#define IsTypeName()          _current_data.type == TYPE_NAME
#define IsArgumentSeparator() _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::ARGUMENT_SEPARATOR
#define IsOperatorSeparator() _current_data.type == SEPARATOR && _current_data.value.keyword_index == (int)KeywordType::OPERATOR_SEPARATOR
#define SE()                  SyntaxError(__LINE__);
#define IsAdd()               _current_data.type == OPERATION && _current_data.value.keyword_index == (int)KeywordType::ADD
#define IsSub()               _current_data.type == OPERATION && _current_data.value.keyword_index == (int)KeywordType::SUB
#define IsMul()               _current_data.type == OPERATION && _current_data.value.keyword_index == (int)KeywordType::MUL
#define IsDiv()               _current_data.type == OPERATION && _current_data.value.keyword_index == (int)KeywordType::DIV
#define IsConst()             _current_data.type == CONST
#define IsAssignment()        _current_data.type == OPERATOR && _current_data.value.keyword_index == (int)KeywordType::ASSIGNMENT
#define IsIn()              _current_data.type == OPERATOR && _current_data.value.keyword_index == (int)KeywordType::IN

#define SHIFT()\
    if(_current_token < context->tokens->size) {\
        (_current_token)++;\
    }\
    else {\
        SE();\
    }\

TYPE_OF_ERROR CreateAstTree(Context* context, Tree<AstNode>* tree) {
    check_expression(context, POINTER_IS_NULL);
    check_expression(tree, POINTER_IS_NULL);

    BufferInit(context->name_table, 5);
    free(tree->root);
    tree->root = GetGrammar(context);
    return SUCCESS;
}

TreeNode<AstNode>* GetGrammar(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(IsBlockClose()) {
        return NULL;
    }

    if(_current_token < context->tokens->size) {
        node = Keyword((int)KeywordType::OPERATOR_SEPARATOR, GetStatement(context), GetGrammar(context));
    }

    return node;
}

TreeNode<AstNode>* GetStatement(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;
    if((node = GetFunctionDefinition(context))) return node;
    if(node = GetVariableDeclaration(context))  return node;
    // if(node = GetAssignment(context))          return node;
    // if(node = GetFunctionCall(context)) {
    //     CheckForSeparator(context);
    //     return node;
    // }
    // if(node = GetWhileStatement(context))      return node;
    // if(node = GetIn(context)) {
    //     CheckForSeparator(context);
    //     return node;
    // }
    // if(node = GetOut(context)) {
    //     CheckForSeparator(context);
    //     return node;
    // }

    SE();

    return node;
}

TreeNode<AstNode>* GetFunctionDefinition(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;
    int start_token = _current_token;
    if(IsTypeName()) {
        TreeNode<AstNode>* return_type = GetReturnType(context);
        SHIFT();
        if(IsWord()) {
            SHIFT();
        }
        else {
            SE();
        }
        if(IsLBracket()) {
            (_current_token)--;
            AddIdentifierToNametable(context);
            SHIFT();
            $DEBUG("%d, %d", _current_name_id, context->tokens->size);
            node = FunctionDefinition(_current_name_id, return_type, Parameters(GetParameters(context), GetGrammar(context)));

            return node;
        }
    }

    _current_token = start_token;
    return node;
}

TreeNode<AstNode>* GetReturnType(Context* context) {
    check_expression(context, NULL);

    #define KEYWORD(NAME, NUMBER, TEXT_RECORD, TYPE)                                             \
        if(TYPE == TYPE_NAME) { \
            return Keyword((int)KeywordType::NAME, NULL, NULL);\
        }

    #include "Keywords.def"

    #undef KEYWORD

    SE();

    return NULL;
}

TreeNode<AstNode>* GetParameters(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;
    SHIFT();
    node = GetParameter(context);
    if(IsRBracket()) {
        SHIFT();
        if(IsBlockOpen()) {
            SHIFT();
            return node;
        }
        SE();
    }
    SE();

    return node;
}

TreeNode<AstNode>* GetParameter(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(IsTypeName()) {
        SHIFT();
        if(IsWord()) {
            AddIdentifierToNametable(context);
            $DEBUG("%d, %d", _current_name_id, context->tokens->size);
            SHIFT();
            if(IsArgumentSeparator()) {
                SHIFT();
            }
            node = Keyword((int)KeywordType::ARGUMENT_SEPARATOR, Identifier(_current_name_id), GetParameter(context));
        }
        else {
            SE();
        }
    }

    return node;
}

TYPE_OF_ERROR AddIdentifierToNametable(Context* context) {
    check_expression(context, POINTER_IS_NULL);

    PushToBuffer<char*>(context->name_table, &(_current_pointer));

    return SUCCESS;
}

TreeNode<AstNode>* GetVariableDeclaration(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;
    if(IsTypeName()) {
        TreeNode<AstNode>* return_type = GetReturnType(context);
        SHIFT();
        if(IsWord()) {
            AddIdentifierToNametable(context);
            SHIFT();
        }
        else {
            SE();
        }
        if(IsAssignment()) {
            SHIFT();
            node = VariableDeclaration(_current_name_id, return_type, GetExpression(context));
        }
        else {
            SE();
        }
    }
    if(IsOperatorSeparator()) {
        SHIFT();
    }
    else {
        SE();
    }

    return node;
}

TreeNode<AstNode>* GetExpression(Context* context) {
    TreeNode<AstNode>* val = GetPlusMinus(context);

    return val;
}

TreeNode<AstNode>* GetPlusMinus(Context* context) {
    TreeNode<AstNode>* val1   = GetMulDiv(context);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;
    int                op     = 0;

    while (IsAdd() || IsSub()) {
        op = _current_value.keyword_index;
        SHIFT();
        val2 = GetPlusMinus(context);
        if(op == (int)KeywordType::ADD) result = Add(val1, val2);
        else                            result = Sub(val1, val2);
    }
    return result;
}

TreeNode<AstNode>* GetMulDiv(Context* context) {
    TreeNode<AstNode>* val1   = GetBracket(context);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;
    int                op     = 0;

    while (IsMul() || IsDiv()) {
        op = _current_value.keyword_index;
        SHIFT();
        val2  = GetMulDiv(context);
        if(op == (int)KeywordType::MUL) result = Mul(val1, val2);
        else                            result = Div(val1, val2);
    }
    return result;
}

TreeNode<AstNode>* GetBracket(Context* context) {
    int sign = 1;
    if(IsSub()) {
        sign = -1;
        SHIFT();
    }
    if(IsLBracket()){
        SHIFT();
        TreeNode<AstNode>* val = GetPlusMinus(context);
        if(IsRBracket()) {
            SHIFT();
        }
        else {
            SE();
        }
        if(!sign) {
            return Mul(Num(-1), val);
        }
        return val;
    }
    else
        if(sign == -1) (_current_token)--;
        return GetFunction(context);
}

TreeNode<AstNode>* GetFunction(Context* context) {
    size_t start = _current_value.keyword_index;
    double amount = 0;
    int    sign   = 1;
    if(IsSub()) {
        sign = -1;
        SHIFT();
    }

    int operation = (int)KeywordType::UNDEFINED;
    #define KEYWORD(NAME, NUMBER, TEXT_RECORD, TYPE, ...)\
        if(_current_data.type == OPERATION && _current_value.keyword_index == NUMBER) {\
            operation = NUMBER;\
        }

    #include "Keywords.def"

    #undef KEYWORD

    TreeNode<AstNode>* val = NULL;
    SHIFT();
    switch(operation) {
        case (int)KeywordType::SQRT:
            val = GetPlusMinus(context);
            $DEBUG("%d", _current_value.keyword_index);
            if(sign == -1) {
                return Mul(Num(-1), Sqrt(val));
            }
            return Sqrt(val);

        case (int)KeywordType::SIN:
            val = GetPlusMinus(context);
            $DEBUG("%s", __func__);
            if(sign == -1) {
                return Mul(Num(-1), Sin(val));
            }
            return Sin(val);

        case (int)KeywordType::COS:
            val = GetPlusMinus(context);
            if(sign == -1) {
                return Mul(Num(-1), Cos(val));
            }
            return Cos(val);

        case (int)KeywordType::FLOOR:
            val = GetPlusMinus(context);
            if(sign == -1) {
                return Mul(Num(-1), Floor(val));
            }
            return Floor(val);

        case (int)KeywordType::UNDEFINED:
            (_current_token)--;
            return GetIdentifier(context);
        default:
            warning(false, PROGRAM_ERROR);
    }
}

TreeNode<AstNode>* GetIdentifier(Context* context) {
    int sign = 1;
    if(IsSub()) {
        sign = -1;
        SHIFT();
    }
    if(IsWord()) {
        AddIdentifierToNametable(context);
        SHIFT();
        if(sign == -1) {
            return Mul(Num(-1), Identifier(_current_name_id));
        }
        return Identifier(_current_name_id);
    }
    if(sign == -1) (_current_token)--;
    return GetNumber(context);
}

TreeNode<AstNode>* GetNumber(Context* context) {
    int    amount = 0;
    int    sign   = 1;

    if(IsSub()) {
        sign = -1;
        SHIFT();
    }

    if(IsConst()) {
        amount = _current_value.int_value;
        amount *= sign;
        SHIFT();
        return Num(amount);
    }

    SE();
}

// TreeNode<AstNode>* GetAssignment(Context* context) {
//     check_expression(context, NULL);
//     int id = -1;
//
//     TreeNode<AstNode>* node = NULL;
//
//     if(IsWord()) {
//         SHIFT();
//         if(id = IsInNametable(context)) {
//             if(IsAssignment()) {
//                 SHIFT();
//                 if(IsIn()) {
//                     node = Keyword((int)KeywordType::ASSIGNMENT, , GetIn(context));
//                 }
//                 else {
//                     node = Keyword((int)KeywordType::ASSIGNMENT, , GetExpression(context));
//                 }
//             }
//             else {
//                 SE();
//             }
//         }
//         else {
//             SE();
//         }
//     }
//
//     return node;
// }
//
// int IsInNametable(Context* context) {
//     check_expression(context, NULL);
//
//     for(int index = 0; index < context->name_table->size; index++) {
//         if(strcmp(_current_pointer, context->name_table->data[index]) == 0) {
//             return index;
//         }
//     }
//
//     return -1;
// }
//
// TreeNode<AstNode>* GetFunctionCall(Context* context) {
//     check_expression(context, NULL);
//
// }
//
// TreeNode<AstNode>* GetArguments(Context* context) {
//
// }
//
// TreeNode<AstNode>* GetWhileStatement(Context* context) {
//     check_expression(context, NULL);
//
// }
//
// TreeNode<AstNode>* GetIn(Context* context) {
//     check_expression(context, NULL);
//
// }
//
// TreeNode<AstNode>* GetOut(Context* context) {
//     check_expression(context, NULL);
//
// }

void SyntaxError(int line) {
    color_printf(RED_COLOR, BOLD, "BRUUUUH Syntax Error in %d\n", line);
    exit(0);
}
