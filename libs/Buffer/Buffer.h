#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "custom_asserts.h"
#include "color_printf.h"
#include "BufferDefinitions.h"


template <typename T>
TYPE_OF_ERROR ReadFile(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    FILE* file = fopen(filename, "r");
    warning(file, POINTER_IS_NULL);

    GetSizeOfBuffer(&(buffer_struct->size), filename);

    buffer_struct->data = (T*)calloc(buffer_struct->size + 1, sizeof(T));
    warning(buffer_struct->data, CALLOC_ERROR);

    ScanFileToBuffer<T>(buffer_struct, filename);

    return SUCCESS;
}

TYPE_OF_ERROR GetSizeOfBuffer(size_t* size, const char* filename) {
    check_expression(size, POINTER_IS_NULL);
    check_expression(filename, POINTER_IS_NULL);

    struct stat buffer_information = {};

    int stat_check = stat(filename, &buffer_information);
    warning(stat_check != -1, STAT_ERROR);

    *size = (size_t)buffer_information.st_size;

    return SUCCESS;
}

template <typename T>
TYPE_OF_ERROR ScanFileToBuffer(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <>
TYPE_OF_ERROR ScanFileToBuffer<char>(Buffer<char>* buffer_struct, const char* filename) {
    check_expression(buffer_struct,      POINTER_IS_NULL);
    check_expression(filename,           POINTER_IS_NULL);
    check_expression(buffer_struct != 0, FILE_READ_ERROR);

    FILE* file = fopen(filename, "r");
    warning(file, FILE_OPEN_ERROR);

    fread(buffer_struct->data, sizeof(char), buffer_struct->size, file);

    fclose(file);

    return SUCCESS;
}

template <typename T>
TYPE_OF_ERROR GetLinePointersFromFile(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <>
TYPE_OF_ERROR GetLinePointersFromFile<char*>(Buffer<char*>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    Buffer<char> text = {};
    ReadFile<char>(&text, filename);

    buffer_struct->size = CountLines(&text, filename);

    buffer_struct->data = (char**)calloc(buffer_struct->size + 1, sizeof(char*));
    warning(buffer_struct->data, CALLOC_ERROR);

    size_t index = 0;
    buffer_struct->data[index] = text.data;
    while(text.data[index] != EOF) {
        if(text.data[index] == '\n')
        buffer_struct->data[index] = &(text.data[index + 1]);
        index++;
    }

    BufferDtor<char>(&text);

    return SUCCESS;
}

template <typename T>
size_t CountLines(Buffer<T>* buffer_struct, const char* filename) {
    check_expression(buffer_struct, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <>
size_t CountLines<char>(Buffer<char>* text, const char* filename) {
    check_expression(text, POINTER_IS_NULL);
    check_expression(filename,      POINTER_IS_NULL);

    size_t lines_number = 0;
    size_t index        = 1;
    while(text->data[index] != EOF) {
        if(text->data[index] == '\n')
            lines_number++;
        index++;
    }

    return lines_number;
}

template <typename T>
TYPE_OF_ERROR BufferDtor(Buffer<T>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    color_printf(RED_COLOR, BOLD, "Please specialize type for %s | FILE: %s | LINE: %d\n",\
                __func__, __FILE__, __LINE__);

    return SUCCESS;
}

template <> //TODO move in BufferSpecializations.h
TYPE_OF_ERROR BufferDtor<char>(Buffer<char>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    buffer_struct->size = 0;
    free(buffer_struct->data);
    buffer_struct->data = NULL;

    return SUCCESS;
}

template <>
TYPE_OF_ERROR BufferDtor<char*>(Buffer<char*>* buffer_struct) {
    check_expression(buffer_struct, POINTER_IS_NULL);

    buffer_struct->size = 0;
    free(buffer_struct->data);
    buffer_struct->data = NULL;

    return SUCCESS;
}

#endif
