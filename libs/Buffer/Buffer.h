#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "color_printf.h"
#include "BufferDefinitions.h"
#include "debug_macros.h"

template <typename T>
inline TYPE_OF_ERROR BufferInit(Buffer<T>* buffer_struct, int capacity) {//TODO fix

    buffer_struct->data = (T*)calloc((size_t)capacity, sizeof(T));
    warning(buffer_struct->data, POINTER_IS_NULL);

    buffer_struct->capacity = capacity;

    return SUCCESS;
}

template <typename T>
inline TYPE_OF_ERROR ReadFile(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    FILE* file = fopen(filename, "r");
    warning(file, POINTER_IS_NULL);

    GetSizeOfFile(&(buffer_struct->capacity), filename);

    buffer_struct->data = (T*)calloc(size_t(buffer_struct->capacity + 1), sizeof(T));

    warning(buffer_struct->data, CALLOC_ERROR);

    ScanFileToBuffer<T>(buffer_struct, filename);

    buffer_struct->size = buffer_struct->capacity;

    return SUCCESS;
}

inline TYPE_OF_ERROR GetSizeOfFile(int* size, const char* filename) {
    check_expression(size,     POINTER_IS_NULL);
    check_expression(filename, POINTER_IS_NULL);

    struct stat buffer_information = {};

    int stat_check = stat(filename, &buffer_information);
    warning(stat_check != -1, STAT_ERROR);

    *size = (int)buffer_information.st_size;

    return SUCCESS;
}

template <typename T>
inline TYPE_OF_ERROR ScanFileToBuffer(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <>
inline TYPE_OF_ERROR ScanFileToBuffer<char>(Buffer<char>* buffer_struct, const char* filename) {
    check_expression(buffer_struct,      POINTER_IS_NULL);
    check_expression(filename,           POINTER_IS_NULL);
    check_expression(buffer_struct != 0, FILE_READ_ERROR);

    FILE* file = fopen(filename, "r");
    warning(file, FILE_OPEN_ERROR);

    fread(buffer_struct->data, sizeof(char), (size_t)buffer_struct->capacity, file);

    fclose(file);

    return SUCCESS;
}

inline TYPE_OF_ERROR GetLinePointersFromFile(Buffer<char*>* buffer_struct, Buffer<char>* text) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(text,          POINTER_IS_NULL);

    buffer_struct->capacity = CountLines(text);

    buffer_struct->data = (char**)calloc((size_t)(buffer_struct->capacity + 1), sizeof(char*));
    warning(buffer_struct->data, CALLOC_ERROR);

    int line_index = 1;
    buffer_struct->data[0] = text->data;
    for(int index = 0; index < text->capacity; index++) {
        if(text->data[index] == '\n') {
            buffer_struct->data[line_index] = &(text->data[index + 1]);
            (buffer_struct->size)++;
            line_index++;
        }
    }

    return SUCCESS;
}



template <typename T>
inline int CountLines(Buffer<T>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <>
inline int CountLines<char>(Buffer<char>* text) {
    check_expression(text, POINTER_IS_NULL);

    int lines_number = 0;
    for(int index = 0; index < text->capacity; index++) {
        if(text->data[index] == '\n') {
            lines_number++;
        }
    }

    return lines_number;
}

template <typename T>
inline TYPE_OF_ERROR PushToBuffer(Buffer<T>* buffer_struct, T* element_to_push) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    if(buffer_struct->size == buffer_struct->capacity) {
        EnlargeBufferCapacity(buffer_struct);
    }

    buffer_struct->data[buffer_struct->size] = *element_to_push;
    (buffer_struct->size)++;

    return SUCCESS;
}

template <typename T>
inline TYPE_OF_ERROR EnlargeBufferCapacity(Buffer<T>* buffer_struct) {
    warning(buffer_struct, POINTER_IS_NULL);

    buffer_struct->data = (T*)realloc(buffer_struct->data, (sizeof(T)*((size_t)(buffer_struct->capacity)*2)));
    buffer_struct->capacity *= 2;

    return SUCCESS;
}

template <typename T>
inline TYPE_OF_ERROR BufferDtor(Buffer<T>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

#endif
