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
    int (*Size)(char* str);
    int (*IsEqual)(char* str1, char* str2);
    char* (*Copy)(char* str);
    char* (*Trim)(char* str);
    char** (*Split)(char* str, char* sep, int* count);
    int (*ToInt)(const char* str);
    double (*ToFloat)(const char* str);
    void (*Free)(char* ptr);
    void (*Free2)(char** ptr, int size);
};
//===============================================
GStringO* GString_New();
void GString_Delete();
GStringO* GString();
//===============================================
#endif
//===============================================
