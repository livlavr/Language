#ifndef DIFF_DUMP_SPECIALIZATIONS_H_
#define DIFF_DUMP_SPECIALIZATIONS_H_

#include "tree.h"
#include "AstDefinitions.h"

#define _WriteOperationDescriptionToStream()                                                                                                          \
    fprintf(dot_file, "P%p [style = \"filled, rounded\", fillcolor=\"yellow:magenta\" gradientangle=270,"                                              \
          "label=\" {Node = [ %p ] | Parent = [ %p ] |"                                                                          \
          " %s | { <l> [ %p ] | <r> [ %p ]}}\" ];\n",                                                                                   \
           node, node, node->parent, operation_symbol[(size_t)(node->value.data.operation)], node->left, node->right)    \

#define _WriteVariableDescriptionToStream()  \
    fprintf(dot_file, "P%p [style = \"filled, rounded\", fillcolor=\"violet:darkcyan\""                                              \
          "label=\" {Node = [ %p ] | Parent = [ %p ] | %c }\" ];\n",                                                                                   \
           node, node, node->parent, variable_table[(size_t)(node->value.data.variable_index)]) \

#define _WriteNumberDescriptionToStream()                                                                                                           \
    fprintf(dot_file, "P%p [style = \"filled, rounded\", fillcolor=\"peachpuff:red\" gradientangle=270,"                                              \
          "label=\" {Node = [ %p ] | Parent = [ %p ] | %.3lf }\" ];\n",                                                                                \
           node, node, node->parent, node->value.data.double_value)                                                              \

template <>
inline TYPE_OF_ERROR ProcessNode<AstNode>(TreeNode<AstNode>* node, FILE* dot_file) {
    check_expression(dot_file,  POINTER_IS_NULL);
    check_expression(node,      POINTER_IS_NULL);

    switch(node->value.type) {
        case number   :
            _WriteNumberDescriptionToStream();
            break;
        case variable :
            _WriteVariableDescriptionToStream();
            break;
        case operation:
            _WriteOperationDescriptionToStream();
            break;
        default:
            color_printf(RED_COLOR, BOLD, "Error in value type choice\n");
            warning     (false, PROGRAM_ERROR);
    }

    return SUCCESS;
}

CONST      = 0,

CYRILLIC_W = 1,
ENGLISH_W  = 1 << 1,

OPERATION  = 1 << 2,

BRACKET    = 1 << 3,
SEPARATOR  = 1 << 4,

OPERATOR   = 1 << 5,

TYPE_NAME  = 1 << 6,
KEYWORD    = 1 << 7,
UNDEFINED  = 1 << 8,

#endif
