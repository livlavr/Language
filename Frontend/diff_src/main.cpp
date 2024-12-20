#include <stdio.h>
#include <cmath>

#include "tree.h"
#include "tree_dump.h"
#include "diff_definitions.h"
#include "diff_dump_specializations.h"
#include "diff_tree_specializations.h"
#include "simplifier.h"
#include "diffIO.h"
#include "latex_output.h"
#include "diff.h"
#include "Buffer.h"

int main() {
    size_t p = 0;
    Tree<DifferentiatorValue> tree = {};
    DiffTreeInit(&tree, {});
    BeginLatexFile();
    Buffer<char> equation = {};
    ReadFile(&equation, "Latex-source/DiffSource.txt");
    ReplaceNodes(&tree, &(tree.root), GetEquation(equation.data, &p));
    TreeDump(&tree);
    SimplifyTree(&tree);
    TreeDump(&tree);
    DerivateTree(&tree);
    TreeDump(&tree);
    SimplifyTree(&tree);
    EndLatexFile();
    OpenDump(&tree);
    TreeDtor(&tree);
    BufferDtor(&equation);
}
