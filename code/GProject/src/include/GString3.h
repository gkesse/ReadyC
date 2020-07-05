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
    void (*ToUpper)(const char* strIn, char* strOut);
    void (*ToLower)(const char* strIn, char* strOut);
    void (*Trim)(const char* strIn, char* strOut);
    void (*SplitGet)(const char* strIn, char* strOut, char* sep, int index);
    int (*SplitCount)(const char* strIn, char* sep);
    void (*Replace)(const char* strIn, char* strOut, const char* pattern, const char* replace);
};
//===============================================
GString3O* GString3_New();
void GString3_Delete();
GString3O* GString3();
//===============================================
#endif
//===============================================