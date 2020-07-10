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
    void (*ToUpper)(const char* strIn, char* strOut);
    void (*ToLower)(const char* strIn, char* strOut);
    void (*Trim)(const char* strIn, char* strOut);
    void (*SplitGet)(const char* strIn, char* strOut, char* sep, int index);
    int (*SplitCount)(const char* strIn, char* sep);
    void (*Replace)(const char* strIn, char* strOut, const char* pattern, const char* replace);
};
//===============================================
GStringO* GString_New();
void GString_Delete();
GStringO* GString();
//===============================================
#endif
//===============================================