#ifndef DIFFIO_H_
#define DIFFIO_H_

TreeNode<DifferentiatorValue>* GetEquation   (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetPlusMinus  (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetMulDiv     (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetPow        (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetVariable   (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetNumber     (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetBracket    (const char* s, size_t* p);
TreeNode<DifferentiatorValue>* GetFunction   (const char* s, size_t* p);
Operations                     ScanOperation (const char* s, size_t* p);
void                           SkipSpaces    (const char* s, size_t* p);
void                           SyntaxError   (int line                );

#define IsSqrt(op) if(strcmp(op, operation_symbol[SQRT]) == 0) return SQRT
#define IsSin( op) if(strcmp(op, operation_symbol[SIN ]) == 0) return SIN
#define IsCos( op) if(strcmp(op, operation_symbol[COS ]) == 0) return COS
#define IsLn(  op) if(strcmp(op, operation_symbol[LN  ]) == 0) return LN
#define IsExp( op) if(strcmp(op, operation_symbol[EXP ]) == 0) return EXP

#define DetectOperation(op)\
    IsSqrt(op);\
    IsSin( op);\
    IsCos( op);\
    IsLn(  op);\
    IsExp( op);\
    else       \
        return UNDEF
#endif
