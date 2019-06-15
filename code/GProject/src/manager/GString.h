//===============================================
#ifndef _GString_
#define _GString_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GStringO GStringO;
//===============================================
struct _GStringO {
    void (*Delete)();
    int (*Size)(const char* str);
    int (*IsEqual)(const char* str1, const char* str2);
    char* (*Copy)(const char* str);
    char* (*Trim)(const char* str);
    char** (*Split)(const char* str, const char* sep, int* count);
    int (*ToInt)(const char* str);
    double (*ToFloat)(const char* str);
    void (*Free)(char* ptr);
    void (*Free2)(char** ptr, const int size);
};
//===============================================
GStringO* GString_New();
void GString_Delete();
GStringO* GString();
//===============================================
#endif
//===============================================
