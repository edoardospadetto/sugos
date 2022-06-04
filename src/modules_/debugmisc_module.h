#ifndef DBGMISC
#define DBGMISC
#include <iostream>
#include <string>
#include "../include/SDL&OpenGL.h"


int countsubstr(const std::string& s, const std::string& target );
/*
template<typename T>
void RecursiveCout(T t);
template<typename T, typename... Args>
void RecursiveCout(T t, Args... args);
template<typename... Args>
void dbglog(Args... args);

template<> void dbglog<char const*>(char const*);
template<> void dbglog<char const*, int>(char const*, int);
template<> void dbglog<unsigned long>(unsigned long);

*/
void printProgramLog( GLuint program );
void printShaderLog( GLuint shader );
#define glCheckError() glCheckError_(__FILE__, __LINE__) 
GLenum glCheckError_(const char *file, int line);
void SugosAssert(bool cnd, const std::string& error_string );
char const* gl_error_string(GLenum const err) noexcept;



template<typename T>
void RecursiveCout(T t)
{

    std::cout << t <<" "<<std::endl;

}
template<typename T, typename... Args>
void RecursiveCout(T t, Args... args)
{

    std::cout << t << " ";
	RecursiveCout(args...);

}

template<typename T>
void add_to_array(T *&array,T value) // add & to make "array" a reference
{
    int size = sizeof(array)/ sizeof(T);
    T *newArr = new T[size + 1];
    memcpy(newArr, array, size * sizeof(T));
    delete[] array;
    array = newArr;
    array[size] = value;
}


template<typename... Args>
void dbglog(Args... args)
{
#ifdef DEBUG
    RecursiveCout(args...) ;
#endif
  

}
#endif

