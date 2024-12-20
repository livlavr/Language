#ifndef DIFF_DSL_H_
#define DIFF_DSL_H_

#define  Num(amount     ) CreateAstNode({.type = NUMBER, .data = {.double_value   = amount   }}, NULL, NULL )
#define  Var(var_index  ) CreateAstNode({.type = variable , .data = {.variable_index = var_index}}, NULL, NULL )
#define  Add(left, right) CreateAstNode({.type = operation, .data = {.operation      = ADD      }}, left, right)
#define  Sub(left, right) CreateAstNode({.type = operation, .data = {.operation      = SUB      }}, left, right)
#define  Mul(left, right) CreateAstNode({.type = operation, .data = {.operation      = MUL      }}, left, right)
#define  Div(left, right) CreateAstNode({.type = operation, .data = {.operation      = DIV      }}, left, right)
#define  Pow(left, right) CreateAstNode({.type = operation, .data = {.operation      = POW      }}, left, right)
#define Sqrt(left       ) CreateAstNode({.type = operation, .data = {.operation      = SQRT     }}, left, NULL )
#define  Sin(left       ) CreateAstNode({.type = operation, .data = {.operation      = SIN      }}, left, NULL )
#define  Cos(left       ) CreateAstNode({.type = operation, .data = {.operation      = COS      }}, left, NULL )
#define   Ln(left       ) CreateAstNode({.type = operation, .data = {.operation      = LN       }}, left, NULL )
#define  Exp(left       ) CreateAstNode({.type = operation, .data = {.operation      = EXP      }}, left, NULL )

#endif
