<<<<<<< HEAD
//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GInclude.h"
//===============================================
#define _EOA_ "_END_OF_ARG_"
//===============================================
typedef struct _GDebugO GDebugO;
//===============================================
struct _GDebugO {
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    void (*Write)(const char* key, ...);
    void (*Clear)();
    void (*Sep)();
    //===============================================
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
=======
//===============================================
#ifndef _GDebug_
#define _GDebug_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDebugO GDebugO;
//===============================================
#define _EOA_ "_END_OF_ARGUMENT_"
//===============================================
#if defined(__unix)
#define GDEBUG_DATA_PATH "/Programs/ReadyC/unix/data/debug"
#elif defined(__WIN32)
#define GDEBUG_DATA_PATH ""
#endif
//===============================================
struct _GDebugO {
	void (*Delete)();
	void (*Test)(int argc, char** argv);
	void (*Write)(const char* key, ...);
	void (*Sep)();
    char m_filename[256];
};
//===============================================
GDebugO* GDebug_New();
void GDebug_Delete();
GDebugO* GDebug();
//===============================================
#endif
//===============================================
>>>>>>> bd9c6b9e67282519751bdf6eeca1c21834218466
