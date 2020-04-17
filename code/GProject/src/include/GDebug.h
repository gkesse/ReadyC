//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDebugO GDebugO;
//===============================================
struct _GDebugO {
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    void (*Write)(const char* key, ...);
    char m_homePath[256];
    char m_debugPath[256];
    char m_filename[256];
};
//===============================================
GDebugO* GDebug_New();
void GDebug_Delete();
GDebugO* GDebug();
//===============================================
#endif
//===============================================
