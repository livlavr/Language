#ifndef BUFFER_SPECIALIZATIONS_H_
#define BUFFER_SPECIALIZATIONS_H_

template <> //TODO move in BufferSpecializations.h
inline TYPE_OF_ERROR BufferDtor<char>(Buffer<char>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    buffer_struct->size = 0;
    free(buffer_struct->data);
    buffer_struct->data = NULL;

    return SUCCESS;
}

template <>
inline TYPE_OF_ERROR BufferDtor<char*>(Buffer<char*>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    buffer_struct->size = 0;
    free(buffer_struct->data);
    buffer_struct->data = NULL;

    return SUCCESS;
}

template <>
inline TYPE_OF_ERROR BufferDtor<Token>(Buffer<Token>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    buffer_struct->size = 0;
    free(buffer_struct->data);
    buffer_struct->data = NULL;

    return SUCCESS;
}

#endif
