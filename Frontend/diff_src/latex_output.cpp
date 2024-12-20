#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "diff_definitions.h"
#include "diff_tree_specializations.h"
#include "latex_output.h"

#include "diff.h"
#include "tree.h"

void BeginLatexFile() {
    FILE* latex_file = fopen("Latex/diff.tex", "w");
    fprintf(latex_file, latex_begining);
    fclose(latex_file);
}

void EndLatexFile() {
    FILE* latex_file = fopen("Latex/diff.tex", "a");
    PrintPhrase(latex_file, latex_ending, latex_ending_size);
    fclose(latex_file);
}

TYPE_OF_ERROR WriteToLatex(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>* node) {
    check_expression(tree, POINTER_IS_NULL);
    check_expression(node, POINTER_IS_NULL);

    FILE* latex_file = fopen("Latex/diff.tex", "a");

    RecursiveWriteToLatex(tree, node, latex_file);

    fclose(latex_file);

    return SUCCESS;
}

TYPE_OF_ERROR RecursiveWriteToLatex(Tree<DifferentiatorValue>* tree, TreeNode<DifferentiatorValue>* node,
                                    FILE* latex_file) {
    check_expression(tree, POINTER_IS_NULL);
    if(!node) return SUCCESS;

    if(node->value.type != operation) {
        PrintValue(node, latex_file);
    }

    #define OPERATOR(OP, LATEX_OUTPUT, ...)\
        if(node->value.type == operation && node->value.data.operation == OP) {\
            LATEX_OUTPUT;\
        }

    #include "codegen.def"

    return SUCCESS;
}

TYPE_OF_ERROR PrintValue(TreeNode<DifferentiatorValue>* node, FILE* latex_file) {

    switch(node->value.type) {
        case operation:
            break;
        case variable:
            fprintf(latex_file, "%c", variable_table[node->value.data.variable_index]);
            break;
        case number:
            fprintf(latex_file, "%0.lf", node->value.data.double_value);
            break;
        default:
            color_printf(RED_COLOR, BOLD, "Error in node type selector");
            check_expression(false, PROGRAM_ERROR);
    }

    return SUCCESS;
}

TYPE_OF_ERROR PrintPhrase(FILE* latex_file, const char* phrase_array[], const size_t size) {
    check_expression(latex_file, POINTER_IS_NULL);
    int phrase_number = rand()%size;

    fprintf(latex_file, phrase_array[phrase_number]);

    return SUCCESS;
}
