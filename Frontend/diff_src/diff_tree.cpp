#include <stdio.h>

#include "diff_definitions.h"
#include "simplifier.h"
#include "tree.h"

static const int ROOT_NODE = 0;

TYPE_OF_ERROR DiffTreeInit(Tree<DifferentiatorValue>* tree, DifferentiatorValue root_value) {
    TreeInit(tree, &root_value);

    return SUCCESS;
}

TreeNode<DifferentiatorValue>* CreateDiffNode(DifferentiatorValue diff_value,
    TreeNode<DifferentiatorValue>* left, TreeNode<DifferentiatorValue>* right) {

    TreeNode<DifferentiatorValue>* new_node = NULL;
    CreateNode<DifferentiatorValue>(&new_node, &diff_value);

    if(left)  LinkNodes<DifferentiatorValue>(new_node, left,  LEFT_SIDE);
    if(right) LinkNodes<DifferentiatorValue>(new_node, right, RIGHT_SIDE);

    return new_node;
}

bool IsEqual(double first_value, double second_value, double eps) {
    return ((first_value - second_value) < eps) && ((second_value - first_value) < eps);
}

TreeNode<DifferentiatorValue>* CopySubtree(TreeNode<DifferentiatorValue>* node) {
    if(!node) return NULL;

    return CreateDiffNode({.type = node->value.type, .data = node->value.data},
                   CopySubtree(node->left), CopySubtree(node->right));
}

TYPE_OF_ERROR   ReplaceNodes(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>** node_before,
                           TreeNode<DifferentiatorValue>* node_after) {
    check_expression(*node_before, POINTER_IS_NULL);
    check_expression(node_after,   POINTER_IS_NULL);

    TreeNode<DifferentiatorValue>* new_node = NULL;
    if(node_after->parent){
        new_node = CopySubtree(node_after);
    }
    else {
        new_node = node_after;
    }

    if((*node_before)->parent) {
        if((*node_before)->parent->left == *node_before) {
            ReplaceSubtree(LEFT_SIDE, new_node);
        }
        else {
            ReplaceSubtree(RIGHT_SIDE, new_node);
        }
    }
    else {
        DestroySubtree<DifferentiatorValue>(node_before);
        tree->root = new_node;
    }

    return SUCCESS;
}

