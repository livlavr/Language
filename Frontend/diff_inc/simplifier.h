#ifndef SIMPLIFIER_H_
#define SIMPLIFIER_H_

bool          IsEqual              (double first_value, double second_value, double eps);
TYPE_OF_ERROR SimplifyTree         (Tree<DifferentiatorValue>* tree);
TYPE_OF_ERROR ReplaceNodes         (Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>** node_before, TreeNode<DifferentiatorValue>* node_after);
TYPE_OF_ERROR RecursiveSimplifyTree(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>** node, size_t* simplifications_number, FILE* latex_file);
TreeNode<DifferentiatorValue>* CopySubtree(TreeNode<DifferentiatorValue>* node);

#define ReplaceSubtree(side, new_node)\
    TreeNode<DifferentiatorValue>* parent_node = (*node_before)->parent;\
    DestroySubtree<DifferentiatorValue>(node_before);\
    LinkNodes(parent_node, new_node, side)

#define EvalTwoArgsOperation(operation) \
    double result = 0;\
    result = (*node)->left->value.data.double_value operation (*node)->right->value.data.double_value;\
    ReplaceNodes(tree, node, Num(result))

#define EvalFunction(function) \
    double result = 0;\
    result = function((*node)->left->value.data.double_value);\
    ReplaceNodes(tree, node, Num(result))

#define IsOperation(OP)\
    (*node)->value.type == operation && (*node)->value.data.operation == OP

#define IsNumber(side)\
    (*node)->side->value.type == number

#define GetValue(side)\
    (*node)->side->value.data.double_value

#define  D(x) RecursiveSubtreeDerivation(tree, x, latex_file)

#define CP(x) CopySubtree(x)


#endif
