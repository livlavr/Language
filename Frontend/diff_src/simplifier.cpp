#include <stdio.h>
#include <math.h>

#include "diff_definitions.h"
#include "diff_dump_specializations.h"
#include "simplifier.h"
#include "diff_DSL.h"
#include "latex_output.h"

#include "diff.h"
#include "tree.h"

TYPE_OF_ERROR SimplifyTree(Tree<DifferentiatorValue>* tree) {
    size_t simplifications_number = 0;

    FILE* latex_file = fopen("Latex/diff.tex", "a");

    PrintPhrase(latex_file, simplify_latex_beginning, simplify_latex_beginning_size);
    fprintf(latex_file, "$$");
    RecursiveWriteToLatex(tree, tree->root, latex_file);
    fprintf(latex_file, "$$\\\\\n");

    do {
        simplifications_number = 0;
        RecursiveSimplifyTree(tree, &(tree->root), &simplifications_number, latex_file);
    }while(simplifications_number != 0);

    fprintf(latex_file, "\\textbf{После упрощения получаем:}\\\\\n");
    fprintf(latex_file, "$$");
    RecursiveWriteToLatex(tree, tree->root, latex_file);
    fprintf(latex_file, "$$\\\\\n");

    fclose(latex_file);

    return SUCCESS;
}

TYPE_OF_ERROR RecursiveSimplifyTree(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>** node,
                                    size_t* simplifications_number, FILE* latex_file) {
    check_expression(simplifications_number, POINTER_IS_NULL);
    if(!(*node)) return SUCCESS;

    RecursiveSimplifyTree(tree, &(*node)->left,  simplifications_number, latex_file);
    RecursiveSimplifyTree(tree, &(*node)->right, simplifications_number, latex_file);

    #define OPERATOR(OP, LATEX_OUTPUT, EVAL_VALUE, LEFT_ZERO_SIMPLIFICATION,      RIGHT_ZERO_SIMPLIFICATION,     \
                                                   LEFT_ONE_SIMPLIFICATION,       RIGHT_ONE_SIMPLIFICATION,      \
                                                   LEFT_MINUS_ONE_SIMPLIFICATION, RIGHT_MINUS_ONE_SIMPLIFICATION,\
                                                   ...)                                                          \
        if(IsOperation(OP)) {                                                                                    \
            if((*node)->right) {                                                                                 \
                if(IsNumber(left)) {                                                                             \
                    if(IsNumber(right)) {                                                                        \
                        EVAL_VALUE;                                                                              \
                    }                                                                                            \
                    else if(IsEqual(GetValue(left),   0, EPS)) {                                                 \
                        LEFT_ZERO_SIMPLIFICATION;                                                                \
                    }                                                                                            \
                    else if(IsEqual(GetValue(left),   1, EPS)) {                                                 \
                        LEFT_ONE_SIMPLIFICATION;                                                                 \
                    }                                                                                            \
                    else if(IsEqual(GetValue(left),  -1, EPS)) {                                                 \
                        LEFT_MINUS_ONE_SIMPLIFICATION;                                                           \
                    }                                                                                            \
                }                                                                                                \
                else if(IsNumber(right)) {                                                                       \
                    if(IsEqual(GetValue(right),       0, EPS)) {                                                 \
                        RIGHT_ZERO_SIMPLIFICATION;                                                               \
                    }                                                                                            \
                    else if(IsEqual(GetValue(right),  1, EPS)) {                                                 \
                        RIGHT_ONE_SIMPLIFICATION;                                                                \
                    }                                                                                            \
                    else if(IsEqual(GetValue(right), -1, EPS)) {                                                 \
                        RIGHT_MINUS_ONE_SIMPLIFICATION;                                                          \
                    }                                                                                            \
                }                                                                                                \
            }                                                                                                    \
            else if(IsNumber(left)) {                                                                            \
                EVAL_VALUE;                                                                                      \
            }                                                                                                    \
        }

    #include "codegen.def"

    return SUCCESS;
}
