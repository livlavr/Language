#include <stdio.h>

#include "custom_asserts.h"
#include "Buffer.h"

TYPE_OF_ERROR TokenizeBuffer(Buffer<char>* buffer, char* tokens) {
    check_expression(buffer, POINTER_IS_NULL);
    check_expression(tokens, POINTER_IS_NULL);


}
