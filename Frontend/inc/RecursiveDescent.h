#ifndef RECURSIVE_DESCENT_H_
#define RECURSIVE_DESCENT_H_

enum Errors {
    NO_ERRORS = 0,
};

struct Context {
    Buffer<Token>*      tokens        = NULL;
    Buffer<char*>*      name_table    = NULL;
    int                 current_token = 0;
    Errors              error         = NO_ERRORS;
    int                 current_scope = -1;
};

TYPE_OF_ERROR      CreateAstTree(Context* context, Tree<AstNode>* tree);
TreeNode<AstNode>* GetGrammar(Context* context);
TreeNode<AstNode>* GetStatement(Context* context);
TreeNode<AstNode>* GetFunctionDefinition(Context* context);
TreeNode<AstNode>* GetReturnType(Context* context);
TreeNode<AstNode>* GetParameters(Context* context);
TreeNode<AstNode>* GetParameter(Context* context);
TYPE_OF_ERROR      AddIdentifierToNametable(Context* context);
TreeNode<AstNode>* GetVariableDeclaration(Context* context);
TreeNode<AstNode>* GetExpression(Context* context);
TreeNode<AstNode>* GetPlusMinus(Context* context);
TreeNode<AstNode>* GetMulDiv(Context* context);
TreeNode<AstNode>* GetBracket(Context* context);
TreeNode<AstNode>* GetFunction(Context* context);
TreeNode<AstNode>* GetIdentifier(Context* context);
TreeNode<AstNode>* GetNumber(Context* context);
// TreeNode<AstNode>* GetAssignment(Context* context);
// TreeNode<AstNode>* GetFunctionCall(Context* context);
// TreeNode<AstNode>* GetWhileStatement(Context* context);
// TreeNode<AstNode>* GetIn(Context* context);
// TreeNode<AstNode>* GetOut(Context* context);
TreeNode<AstNode>* CheckForSeparator(Context* context);
void               SyntaxError(int line);
int                IsInNametable(Context* context);
#endif
