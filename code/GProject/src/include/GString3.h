//===============================================
#ifndef _GString3_
#define _GString3_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GString3O GString3O;
//===============================================
struct _GString3O {
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
GString3O* GString3_New();
void GString3_Delete();
GString3O* GString3();
//===============================================
#endif
//===============================================