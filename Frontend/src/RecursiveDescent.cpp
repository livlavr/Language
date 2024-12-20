#include <stdio.h>

// #define NDEBUG

#include "tree.h"
#include "AstDefinitions.h"
#include "debug_macros.h"

TreeNode<AstNode>* GetEquation(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* val = GetPlusMinus(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    if(s[*p] != '\0' && s[*p] != '\n')
        SyntaxError(__LINE__);
    return val;
}

TreeNode<AstNode>* GetPlusMinus(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* val1   = GetMulDiv(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;

    while (s[*p] == '+' || s[*p] == '-') {
        int op = s[*p];
        (*p)++;
        val2 = GetPlusMinus(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p]);
        if(op == '+') result = Add(val1, val2);
        else          result = Sub(val1, val2);
    }
    SkipSpaces(s, p);
    return result;
}

TreeNode<AstNode>* GetMulDiv(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* val1   = GetPow(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;

    while (s[*p] == '*' || s[*p] == '/') {
        int op = s[*p];
        (*p)++;
        val2  = GetMulDiv(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p]);
        if(op == '*') result = Mul(val1, val2);
        else          result = Div(val1, val2);
    }
    SkipSpaces(s, p);
    return result;
}

TreeNode<AstNode>* GetPow(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* val1   = GetBracket(s, p);
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    TreeNode<AstNode>* result = val1;
    TreeNode<AstNode>* val2   = NULL;

    while (s[*p] == '^') {
        (*p)++;
        val2   = GetPow(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p]);
        result = Pow(val1, val2);
    }
    SkipSpaces(s, p);
    return result;
}

TreeNode<AstNode>* GetBracket(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    SkipSpaces(s, p);
    int sign = 1;
    if(s[*p] == '-') {
        sign = -1;
        (*p)++;
    }
    if(s[*p] == '('){
        (*p)++;
        SkipSpaces(s, p);
        TreeNode<AstNode>* val = GetPlusMinus(s, p);
        $DEBUG("%s", __func__);
        $DEBUG("%c", s[*p]);
        if(s[*p] != ')')
            SyntaxError(__LINE__);
        (*p)++;
        SkipSpaces(s, p);
        if(!sign) {
            return Mul(Num(-1), val);
        }
        return val;
    }
    else
        if(sign == -1) (*p)--;
        return GetFunction(s, p);
}

TreeNode<AstNode>* GetFunction(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    size_t start = *p;
    double amount = 0;
    int    sign   = 1;
    if(s[*p] == '-') {
        sign = -1;
        (*p)++;
    }
    Operations op = ScanOperation(s, p);
    TreeNode<AstNode>* val = NULL;
    (*p)++;
    SkipSpaces(s, p);
    switch(op) {
        case SQRT:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p]);
            if(s[*p] != ')')
                SyntaxError(__LINE__);
            (*p)++;
            SkipSpaces(s, p);
            if(sign == -1) {
                return Mul(Num(-1), Sqrt(val));
            }
            return Sqrt(val);

        case SIN:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p]);
            if(s[*p] != ')')
                SyntaxError(__LINE__);
            (*p)++;
            SkipSpaces(s, p);
            if(sign == -1) {
                return Mul(Num(-1), Sin(val));
            }
            return Sin(val);

        case COS:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p]);
            if(s[*p] != ')')
                SyntaxError(__LINE__);
            (*p)++;
            SkipSpaces(s, p);
            if(sign == -1) {
                return Mul(Num(-1), Cos(val));
            }
            return Cos(val);

        case LN:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p]);
            if(s[*p] != ')')
                SyntaxError(__LINE__);
            (*p)++;
            SkipSpaces(s, p);
            if(sign == -1) {
                return Mul(Num(-1), Ln(val));
            }
            return Ln(val);

        case EXP:
            val = GetPlusMinus(s, p);
            $DEBUG("%s", __func__);
            $DEBUG("%c", s[*p]);
            if(s[*p] != ')')
                SyntaxError(__LINE__);
            (*p)++;
            SkipSpaces(s, p);
            if(sign == -1) {
                return Mul(Num(-1), Exp(val));
            }
            return Exp(val);

        case UNDEF:
            *p = start;
            return GetVariable(s, p);
        default:
            warning(false, PROGRAM_ERROR);
    }
}

TreeNode<AstNode>* GetVariable(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    size_t number_of_var = sizeof(variable_table);
    int    sign   = 1;
    if(s[*p] == '-') {
        sign = -1;
        (*p)++;
    }
    for(size_t variable_number = 0; variable_number < number_of_var; variable_number++) {
        if(s[*p] == variable_table[variable_number]) {
            (*p)++;
            SkipSpaces(s, p);
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

TreeNode<AstNode>* GetNumber(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    SkipSpaces(s, p);
    double amount = 0;
    size_t start  = *p;
    int    sign   = 1;
    if(s[*p] == '-') {
        sign = -1;
        (*p)++;
    }
    while('0' <= s[*p] && s[*p] <= '9') {
        amount = amount * 10 + (s[*p] - '0');
        (*p)++;
    }
    if(start == *p)
        SyntaxError(__LINE__);
    SkipSpaces(s, p);
    amount *= sign;
    return Num(amount);
}

Operations ScanOperation(const char* s, size_t* p) {
    $DEBUG("%s", __func__);
    $DEBUG("%c", s[*p]);
    SkipSpaces(s, p);
    char       operation[6] = "";
    size_t     op_index     = 0;
    Operations op;
    while(s[*p] != '(' && s[*p] != '\0' && op_index < 6) {
        operation[op_index] = s[*p];
        (*p)++;
        SkipSpaces(s, p);
        op_index++;
    }
    DetectOperation(operation);
}

void SyntaxError(int line){
    color_printf(RED_COLOR, BOLD, "BRUUUUH Syntax Error in %d\n", line);
    exit(0);
}

void SkipSpaces(const char* s, size_t* p) {
    while(s[*p] == ' ') {
        (*p)++;
    };
}
