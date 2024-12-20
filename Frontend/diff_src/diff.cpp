#include <stdio.h>

#include "diff_definitions.h"
#include "diff_tree_specializations.h"
#include "simplifier.h"
#include "diff_DSL.h"
#include "latex_output.h"
#include "diff.h"
#include "tree.h"

TYPE_OF_ERROR DerivateTree(Tree<DifferentiatorValue>* tree) {
    check_expression(tree, POINTER_IS_NULL);

    FILE* latex_file = fopen("Latex/diff.tex", "a");
    PrintPhrase(latex_file, derivation_latex_beginning, derivation_latex_beginning_size);

    ReplaceNodes(tree, &(tree->root), RecursiveSubtreeDerivation(tree, tree->root, latex_file));

    fclose(latex_file);

    return SUCCESS;
}

TreeNode<DifferentiatorValue>* RecursiveSubtreeDerivation(Tree<DifferentiatorValue>* tree,
                                    TreeNode<DifferentiatorValue>* node, FILE* latex_file) {
    if(!node) return NULL;

    TreeNode<DifferentiatorValue>* diff_result = NULL;

    if(node->value.type == variable) {
        diff_result = Num(1);
        LatexOutput();
    }
    else if(node->value.type == number) {
        diff_result = Num(0);
        LatexOutput();
    }

    #define OPERATOR(OP, LATEX_OUTPUT, EVAL_VALUE, LEFT_ZERO_SIMPLIFICATION,      RIGHT_ZERO_SIMPLIFICATION,      \
                                                   LEFT_ONE_SIMPLIFICATION,       RIGHT_ONE_SIMPLIFICATION,       \
                                                   LEFT_MINUS_ONE_SIMPLIFICATION, RIGHT_MINUS_ONE_SIMPLIFICATION, \
                                                   DIFFERENTIATED)                                                \
        if(node->value.type == operation && node->value.data.operation == OP) {                                   \
            DIFFERENTIATED;                                                                                       \
            LatexOutput();                                                                                        \
        }

    #include "codegen.def"

    return diff_result;
}
