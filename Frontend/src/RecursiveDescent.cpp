#include <stdio.h>
#include <string.h>
// #define NDEBUG

#include "tree.h"
#include "AstDefinitions.h"
#include "Tokenization.h"
#include "BufferSpecializations.h"
#include "OperationsDSL.h"
#include "debug_macros.h"

enum Errors {
    NO_ERRORS = 0;
};

struct Identifier {
    char* name = NULL;
    int   id   = -1;
};

struct Context {
    Buffer<Token>*      tokens        = NULL;
    Buffer<Identifier>* name_table    = NULL;
    int                 current_token = 0;
    Errors              error         = NO_ERRORS;
    int                 current_scope = -1;
};

#define _current_token   context->current_token
#define _tokens          context->tokens
#define _current_name_id context->name_table->size
#define _current_symbol  _tokens[_current_token].data->value.text_pointer[0]

TYPE_OF_ERROR CreateAstTree(Context* context, Tree<AstNode>* tree) {
    check_expression(context, POINTER_IS_NULL);
    check_expression(tree, POINTER_IS_NULL);

    BufferInit(context->name_table, 5);
    tree->root = GetGrammar(context);

    return SUCCESS;
}

TreeNode<AstNode>* GetGrammar(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;
    if(context->current_token + 1 != context->tokens->size) {
        node = Keyword(SEPARATOR, GetStatement(context), GetGrammar(context));
    }

    return node;
}

TreeNode<AstNode>* GetStatement(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(node = GetFunctionDefinition(context)) return node;
    if(node = GetVariableDeclaration(context)) return node;
    if(node = GetAssignment(context))          return node;
    if(node = GetFunctionCall(context)) {
        CheckForSeparator(context);
        return node;
    }
    if(node = GetWhileStatement(context))      return node;
    if(node = GetIn(context)) {
        CheckForSeparator(context);
        return node;
    }
    if(node = GetOut(context)) {
        CheckForSeparator(context);
        return node;
    }

    SyntaxError();
}

TreeNode<AstNode>* GetFunctionDefinition(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(_tokens[_current_token].data->type == TYPE_NAME) {
        TreeNode<AstNode>* return_type = GetReturnType(context);
        (_current_token)++;
        AddIdentifierToNametable(context);
        (_current_token)++;
        node = FunctionDefinition(_current_name_id, return_type, GetParameters(context));
    }

    return node;
}
//int function(int hui, int elda)
//int function()
TreeNode<AstNode>* GetReturnType(Context* context) {
    check_expression(context, NULL);

    #define KEYWORD(NAME, NUMBER, TEXT_RECORD, TYPE, ...)                                             \
        if(TYPE == TYPE_NAME && strncmp(&(_current_symbol), TEXT_RECORD, strlen(TEXT_RECORD)) == 0) { \
            return NAME;                                                                              \
        }

    #include "Keywords.def"

    #undef KEYWORD
}

TreeNode<AstNode>* GetParameters(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(_current_symbol == '(') {
        (_current_token)++;
        GetParameter(context);
        if(_current_symbol != ')') {
            SyntaxError(__LINE__);
        }
    }

    return node;
}

TreeNode<AstNode>* GetParameter(Context* context) {
    check_expression(context, NULL);

    TreeNode<AstNode>* node = NULL;

    if(_tokens[_current_token].data->type == TYPE_NAME) {
        (_current_token)++;
        if(_tokens[_current_token].data->type == ENGLISH_W || _tokens[_current_token].data->type == CYRILLIC_W) {
            AddIdentifierToNametable(context);
            node = Keyword((int)KeywordType::ARGUMENT_SEPARATOR, GetParameter(context), Identifier(_current_name_id));
            (_current_token)++;
        }
        else {
            SyntaxError(__LINE__);
        }
    }

    return node;
}

TreeNode<AstNode>* AddIdentifierToNametable(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetVariableDeclaration(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetAssignment(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetFunctionCall(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetWhileStatement(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetIn(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* GetOut(Context* context) {
    check_expression(context, NULL);

}

TreeNode<AstNode>* CheckForSeparator(Context* context) {
    check_expression(context, NULL);

}

void SyntaxError(int line){
    color_printf(RED_COLOR, BOLD, "BRUUUUH Syntax Error in %d\n", line);
    exit(0);
}
