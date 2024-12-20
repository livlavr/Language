#ifndef DIFF_TREE_SPECIALIZATIONS_H_
#define DIFF_TREE_SPECIALIZATIONS_H_

template <>
inline TreeErrors TreeInit<DifferentiatorValue>(Tree<DifferentiatorValue>* tree, const DifferentiatorValue* diff_value) {
    check_expression(tree, NODE_POINTER_IS_NULL);

    tree->error           = NO_TREE_ERRORS;
    tree->root            = NULL;
    tree->dump_svg_file   = NULL;
    tree->dump_html_file  = NULL;
    CreateNode<DifferentiatorValue>(&(tree->root), diff_value);
    SetDumpFile(tree);

    return NO_TREE_ERRORS;
}

template <>
inline TreeErrors AddNode<DifferentiatorValue>(TreeNode<DifferentiatorValue>* node, const DifferentiatorValue* diff_value, int connection_side) {
    check_expression(node, NODE_POINTER_IS_NULL);

    TreeNode<DifferentiatorValue>* new_node = NULL;
    CreateNode(&new_node,      diff_value     );
    LinkNodes (node, new_node, connection_side);

    return NO_TREE_ERRORS;
}

#endif
