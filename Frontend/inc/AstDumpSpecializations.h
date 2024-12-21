#ifndef DIFF_DUMP_SPECIALIZATIONS_H_
#define DIFF_DUMP_SPECIALIZATIONS_H_

#include "tree.h"
#include "AstDefinitions.h"
#include "debug_macros.h"

#define _WriteStartOfDescription(color)  \
    fprintf(dot_file, "P%p [style = \"filled, rounded\", fillcolor=\"" color "\""                  \
          "label=\" {Node = [ %p ] | Parent = [ %p ] |", node, node, node->parent)

#define _WriteEndOfDescription()  \
    fprintf(dot_file, "| { <l> [ %p ] | <r> [ %p ]}}\" ];\n", node->left, node->right)

#define _WriteIdentifierDescription()\
    fprintf(dot_file, " IDENTIFIER | %d ",          \
            node->value.data.id)

#define _WriteFunctionDefinitionDescription()\
    fprintf(dot_file, " FUNCTION_DEFINITION | %d ",          \
            node->value.data.id)

#define _WriteParametersDescription()\
    fprintf(dot_file, " PARAMETERS | %d ",          \
            node->value.data.id)

#define _WriteVarDeclarationDescription()\
    fprintf(dot_file, " VAR_DECLARATION | %d ",          \
            node->value.data.id)

#define _WriteFunctionCallDescription()\
    fprintf(dot_file, " FUNCTION_CALL | %d ",          \
            node->value.data.id)

#define _WriteConstDescription() \
    fprintf(dot_file, " CONSTANT | %d ",          \
            node->value.data.int_value)

template <>
inline TYPE_OF_ERROR ProcessNode<AstNode>(TreeNode<AstNode>* node, FILE* dot_file) {
    check_expression(dot_file,  POINTER_IS_NULL);
    check_expression(node,      POINTER_IS_NULL);

    #define KEYWORD(NAME, NUMBER, TEXT_RECORD, TYPE, ...)\
        if(node->value.data.id == NUMBER) {\
            fprintf(dot_file, " %s | %d", TEXT_RECORD, NUMBER);\
        }

    switch(node->value.type) {
        case AstNodeType::CONSTANT:
            _WriteStartOfDescription("#5e69db");
            _WriteConstDescription();
            _WriteEndOfDescription();
            break;

        case AstNodeType::IDENTIFIER:
            _WriteStartOfDescription("#c95410");
            _WriteIdentifierDescription();
            _WriteEndOfDescription();
            break;

        case AstNodeType::KEYWORD:
            _WriteStartOfDescription("#45c1ff");
            #include "Keywords.def"
            _WriteEndOfDescription();
            break;

        case AstNodeType::FUNCTION_DEFINITION:
            _WriteStartOfDescription("#c9b0a1");
            _WriteFunctionDefinitionDescription();
            _WriteEndOfDescription();
            break;

        case AstNodeType::PARAMETERS:
            _WriteStartOfDescription("#dbd802");
            _WriteParametersDescription();
            _WriteEndOfDescription();
            break;

        case AstNodeType::VAR_DECLARATION:
            _WriteStartOfDescription("#a1c9a7");
            _WriteVarDeclarationDescription();
            _WriteEndOfDescription();
            break;

        case AstNodeType::FUNCTION_CALL:
            _WriteStartOfDescription("#c224ce");
            _WriteFunctionCallDescription();
            _WriteEndOfDescription();
            break;

        default:
            color_printf(RED_COLOR, BOLD, "Error in value type choice\n");
            warning     (false, PROGRAM_ERROR);
    }

    #undef KEYWORD

    return SUCCESS;
}

/*
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

*/

#endif
