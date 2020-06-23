//===============================================
#ifndef _GDir2_
#define _GDir2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDir2O GDir2O;
//===============================================
#if defined(__unix)
#define GDIR_DATA_PATH "/Programs/ReadyC/unix/"
#elif defined(__WIN32)
#define GDIR_DATA_PATH ""
#endif
//===============================================
struct _GDir2O {
	void (*Delete)();
	void (*Test)(int argc, char** argv);
	void (*DataPath)(char* path, char* output);
    char m_homePath[256];
    char m_dataPath[256];
};
//===============================================
GDir2O* GDir2_New();
void GDir2_Delete();
GDir2O* GDir2();
//===============================================
#endif
//===============================================
