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

static const int ROOT_NODE = 0;

TYPE_OF_ERROR AstTreeInit(Tree<AstNode>* tree, AstNode root_value) {
    TreeInit(tree, &root_value);

    return SUCCESS;
}

// TreeNode<AstNode>* CopySubtree(TreeNode<AstNode>* node) {
//     if(!node) return NULL;
//
//     return CreateAstNode({.type = node->value.type, .data = node->value.data},
//                    CopySubtree(node->left), CopySubtree(node->right));
// }

// TYPE_OF_ERROR   ReplaceNodes(Tree<AstNode>* tree, TreeNode<AstNode>** node_before,
//                            TreeNode<AstNode>* node_after) {
//     check_expression(*node_before, POINTER_IS_NULL);
//     check_expression(node_after,   POINTER_IS_NULL);
//
//     TreeNode<AstNode>* new_node = NULL;
//     if(node_after->parent){
//         new_node = CopySubtree(node_after);
//     }
//     else {
//         new_node = node_after;
//     }
//
//     if((*node_before)->parent) {
//         if((*node_before)->parent->left == *node_before) {
//             ReplaceSubtree(LEFT_SIDE, new_node);
//         }
//         else {
//             ReplaceSubtree(RIGHT_SIDE, new_node);
//         }
//     }
//     else {
//         DestroySubtree<AstNode>(node_before);
//         tree->root = new_node;
//     }
//
//     return SUCCESS;
// }
