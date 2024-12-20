#ifndef DIFF_H_
#define DIFF_H_

TYPE_OF_ERROR DerivateTree(Tree<DifferentiatorValue>* tree);
TreeNode<DifferentiatorValue>* RecursiveSubtreeDerivation(Tree<DifferentiatorValue>* tree,
                                    TreeNode<DifferentiatorValue>* node, FILE* latex_file);

#ifndef NDEBUG
    #define WriteIfDebug(expression) expression
#else
    #define WriteIfDebug(expression)
#endif

#define RIGHT\
    node->right

#define LEFT\
    node->left

#define I_MADE_CHANGES\
    (*simplifications_number)++

#endif
