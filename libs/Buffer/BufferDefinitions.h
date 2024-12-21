#ifndef BUFFER_DEFINITIONS_H_
#define BUFFER_DEFINITIONS_H_

template <typename T>
struct Buffer {
    T*     data     = NULL;
    int    size     = 0;
    int    capacity = 0;
};

template <typename T> inline TYPE_OF_ERROR ReadFile               (Buffer<T>* buffer_struct, const char* filename);
template <typename T> inline TYPE_OF_ERROR ScanFileToBuffer       (Buffer<T>* buffer_struct, const char* filename);
template <          > inline TYPE_OF_ERROR ScanFileToBuffer<char> (Buffer<char>* buffer_struct, const char* filename);
TYPE_OF_ERROR         inline               GetSizeOfFile          (int* size, const char* filename);
template <typename T> inline int           CountLines             (Buffer<T>* buffer_struct);
template <          > inline int           CountLines<char>       (Buffer<char>* text);
                      inline TYPE_OF_ERROR GetLinePointersFromFile(Buffer<char*>* buffer_struct, Buffer<char>* text);
template <typename T> inline TYPE_OF_ERROR BufferDtor             (Buffer<T>* buffer_struct);
template <          > inline TYPE_OF_ERROR BufferDtor<char>       (Buffer<char>* buffer_struct);
template <          > inline TYPE_OF_ERROR BufferDtor<char*>      (Buffer<char*>* buffer_struct);
template <typename T> inline TYPE_OF_ERROR PushToBuffer           (Buffer<T>* buffer_struct, T* element_to_push);
template <typename T> inline TYPE_OF_ERROR EnlargeBufferCapacity  (Buffer<T>* buffer_struct);
template <typename T> inline TYPE_OF_ERROR BufferInit             (Buffer<T>* buffer_struct, int capacity);

#endif
