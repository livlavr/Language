#ifndef DIFF_DEFINITIONS_H_
#define DIFF_DEFINITIONS_H_

#include <stdio.h>
#include <math.h>

#include "tree.h"

static const char*  operation_symbol[] = {"+", "-", "*", "/", "sqrt", "sin", "cos", "ln", "exp", "^"};
static const char   variable_table  [] = {'x', 'y', 'z'}; //TODO change to template struct Buffer<...>
static const double EPS = 1e-5;

enum NodeType{
    number    = 0,
    variable  = 1,
    operation = 1 << 1,
};

enum Operations {
    UNDEF = -1,
    ADD   = 0,
    SUB   = 1,
    MUL   = 2,
    DIV   = 3,
    SQRT  = 4,
    SIN   = 5,
    COS   = 6,
    LN    = 7,
    EXP   = 8,
    POW   = 9,
};

union NodeValue{
    double     double_value;
    size_t     variable_index;
    Operations operation;
};

struct DifferentiatorValue{
    NodeType   type;
    NodeValue  data = {.double_value = NAN};
};

TreeNode<DifferentiatorValue>* CreateDiffNode(DifferentiatorValue diff_value,
                TreeNode<DifferentiatorValue>* left, TreeNode<DifferentiatorValue>* right);
TYPE_OF_ERROR DiffTreeInit(Tree<DifferentiatorValue>* tree, DifferentiatorValue root_value);

#endif
