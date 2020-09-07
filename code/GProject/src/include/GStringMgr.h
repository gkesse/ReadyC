//===============================================
#ifndef _GStringMgr_
#define _GStringMgr_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GStringMgrO GStringMgrO;
//===============================================
struct _GStringMgrO {
    void (*Delete)();
    char* (*Copy)(const char* strIn);
    void (*ToUpper)(const char* strIn, char* strOut);
    void (*ToLower)(const char* strIn, char* strOut);
    void (*Trim)(const char* strIn, char* strOut);
    void (*SplitGet)(const char* strIn, char* strOut, char* sep, int index);
    int (*SplitCount)(const char* strIn, char* sep);
    void (*Replace)(const char* strIn, char* strOut, const char* pattern, const char* replace);
};
//===============================================
GStringMgrO* GStringMgr_New();
void GStringMgr_Delete();
GStringMgrO* GStringMgr();
//===============================================
#endif
//===============================================