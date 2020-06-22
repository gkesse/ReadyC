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
    void (*Test)(int argc, char** argv);
    char* (*Trim)(char* str);
    char* (*Copy)(char* str);
    char** (*Split)(char* str, char* sep, int* count);
    void (*ToUpper)(char* str, char* output);
    void (*ToLower)(char* str, char* output);
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