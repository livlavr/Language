#ifndef BUFFER_DEFINITIONS_H_
#define BUFFER_DEFINITIONS_H_

template <typename T>
struct Buffer {
    T*     data = NULL;
    size_t size = 0;
};

template <typename T> TYPE_OF_ERROR ReadFile              (Buffer<T>* buffer_struct, const char* filename);
template <typename T> TYPE_OF_ERROR ScanFileToBuffer      (Buffer<T>* buffer_struct, const char* filename);
template <          > TYPE_OF_ERROR ScanFileToBuffer<char>(Buffer<char>* buffer_struct, const char* filename);
TYPE_OF_ERROR GetSizeOfBuffer(size_t* size, const char* filename);

#endif
