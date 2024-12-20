#include <stdio.h>

#include "AstDefinitions.h"

TreeNode<AstNode>* CreateAstNode(AstNode ast_value,
    TreeNode<AstNode>* left, TreeNode<AstNode>* right) {

    TreeNode<AstNode>* new_node = NULL;
    CreateNode<AstNode>(&new_node, &ast_value);

    if(left)  LinkNodes<AstNode>(new_node, left,  LEFT_SIDE);
    if(right) LinkNodes<AstNode>(new_node, right, RIGHT_SIDE);

    return new_node;
}
