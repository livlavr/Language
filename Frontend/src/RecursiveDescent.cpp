#include <stdio.h>

// #define NDEBUG

#include "tree.h"
#include "AstDefinitions.h"
#include "Tokenization.h"
#include "BufferSpecializations.h"
#include "OperationsDSL.h"
#include "debug_macros.h"

TreeNode<AstNode>* GetEquation(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    TreeNode<AstNode>* val = GetPlusMinus(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    if(s[*p].data->value.text_pointer[0] != '\0' && s[*p].data->value.text_pointer[0] != '\n')
        SyntaxError(__LINE__);
    return val;
}

TreeNode<AstNode>* GetPlusMinus(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    TreeNode<AstNode>* val1   = GetMulDiv(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;

    while (s[*p].data->value.text_pointer[0] == '+' || s[*p].data->value.text_pointer[0] == '-') {
        int op = s[*p].data->value.text_pointer[0];
        (*p)++;
        val2 = GetPlusMinus(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p].data->value.text_pointer[0]);
        if(op == '+') result = Add(val1, val2);
        else          result = Sub(val1, val2);
    }

    return result;
}

TreeNode<AstNode>* GetMulDiv(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    TreeNode<AstNode>* val1   = GetBracket(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;

    while (s[*p].data->value.text_pointer[0] == '*' || s[*p].data->value.text_pointer[0] == '/') {
        int op = s[*p].data->value.text_pointer[0];
        (*p)++;
        val2  = GetMulDiv(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p].data->value.text_pointer[0]);
        if(op == '*') result = Mul(val1, val2);
        else          result = Div(val1, val2);
    }

    return result;
}

TreeNode<AstNode>* GetBracket(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);

    int sign = 1;
    if(s[*p].data->value.text_pointer[0] == '-') {
        sign = -1;
        (*p)++;
    }
    if(s[*p].data->value.text_pointer[0] == '('){
        (*p)++;

        TreeNode<AstNode>* val = GetPlusMinus(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p].data->value.text_pointer[0]);
        if(s[*p].data->value.text_pointer[0] != ')')
            SyntaxError(__LINE__);
        (*p)++;

        if(!sign) {
            return Mul(Num(-1), val);
        }
        return val;
    }
    else
        if(sign == -1) (*p)--;
        return GetFunction(s, p);
}

TreeNode<AstNode>* GetFunction(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    int start = *p;
    double amount = 0;
    int    sign   = 1;
    if(s[*p].data->value.text_pointer[0] == '-') {
        sign = -1;
        (*p)++;
    }
    Operations op = ScanOperation(s, p);
    TreeNode<AstNode>* val = NULL;
    (*p)++;

    switch(op) {
        case SQRT:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p].data->value.text_pointer[0]);
            if(s[*p].data->value.text_pointer[0] != ')')
                SyntaxError(__LINE__);
            (*p)++;

            if(sign == -1) {
                return Mul(Num(-1), Sqrt(val));
            }
            return Sqrt(val);

        case SIN:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p].data->value.text_pointer[0]);
            if(s[*p].data->value.text_pointer[0] != ')')
                SyntaxError(__LINE__);
            (*p)++;

            if(sign == -1) {
                return Mul(Num(-1), Sin(val));
            }
            return Sin(val);

        case COS:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p].data->value.text_pointer[0]);
            if(s[*p].data->value.text_pointer[0] != ')')
                SyntaxError(__LINE__);
            (*p)++;

            if(sign == -1) {
                return Mul(Num(-1), Cos(val));
            }
            return Cos(val);

        case UNDEF:
            *p = start;
            return GetVariable(s, p);
        default:
            warning(false, PROGRAM_ERROR);
    }
}

TreeNode<AstNode>* GetVariable(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);
    int number_of_var = sizeof(variable_table);
    int    sign   = 1;
    if(s[*p].data->value.text_pointer[0] == '-') {
        sign = -1;
        (*p)++;
    }
    for(int variable_number = 0; variable_number < number_of_var; variable_number++) {
        if(s[*p].data->value.text_pointer[0] == variable_table[variable_number]) {
            (*p)++;

            $DEBUG("%d", variable_number);
            if(sign == -1) {
                return Mul(Num(-1), Var(variable_number));
            }
            return Var(variable_number);
        }
    }
    if(sign == -1) (*p)--;
    return GetNumber(s, p);
}

TreeNode<AstNode>* GetNumber(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);

    double amount = 0;
    int start  = *p;
    int    sign   = 1;
    if(s[*p].data->value.text_pointer[0] == '-') {
        sign = -1;
        (*p)++;
    }
    while('0' <= s[*p].data->value.text_pointer[0] && s[*p].data->value.text_pointer[0] <= '9') {
        amount = amount * 10 + (s[*p].data->value.text_pointer[0] - '0');
        (*p)++;
    }
    if(start == *p)
        SyntaxError(__LINE__);

    amount *= sign;
    return Num(amount);
}

Operations ScanOperation(const Buffer<Token>* s, int* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p].data->value.text_pointer[0]);

    char       operation[6] = "";
    int     op_index     = 0;
    Operations op;
    while(s[*p].data->value.text_pointer[0] != '(' && s[*p].data->value.text_pointer[0] != '\0' && op_index < 6) {
        operation[op_index] = s[*p].data->value.text_pointer[0];
        (*p)++;

        op_index++;
    }
    DetectOperation(operation);
}

void SyntaxError(int line){
    color_printf(RED_COLOR, BOLD, "BRUUUUH Syntax Error in %d\n", line);
    exit(0);
}
