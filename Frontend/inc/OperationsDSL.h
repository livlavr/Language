#ifndef OPERATIONS_DSL_H_
#define OPERATIONS_DSL_H_

//TODO scope
#define  Num(amount     ) CreateAstNode({.type = CONSTANT,    .data = {.double_value   = amount   }}, NULL, NULL )
#define  Var(var_index  ) CreateAstNode({.type = IDENTIFIER , .data = {.identifier     = var_index}}, NULL, NULL )
#define  Add(left, right) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = ADD      }}, left, right)
#define  Sub(left, right) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = SUB      }}, left, right)
#define  Mul(left, right) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = MUL      }}, left, right)
#define  Div(left, right) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = DIV      }}, left, right)
#define Sqrt(left       ) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = SQRT     }}, left, NULL )
#define  Sin(left       ) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = SIN      }}, left, NULL )
#define  Cos(left       ) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = COS      }}, left, NULL )
#define   Ln(left       ) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = LN       }}, left, NULL )
#define  Exp(left       ) CreateAstNode({.type = IDENTIFIER, .data = {.identifier      = EXP      }}, left, NULL )

#endif
