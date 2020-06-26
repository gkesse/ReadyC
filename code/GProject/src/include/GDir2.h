//===============================================
#ifndef _GDir_
#define _GDir_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDirO GDirO;
//===============================================
#if defined(__unix)
#define GDIR_DATA_PATH "/Programs/ReadyC/unix/"
#elif defined(__WIN32)
#define GDIR_DATA_PATH ""
#endif
//===============================================
struct _GDirO {
	void (*Delete)();
	void (*Test)(int argc, char** argv);
	void (*DataPath)(char* path, char* output);
    char m_homePath[256];
    char m_dataPath[256];
};
//===============================================
GDirO* GDir_New();
void GDir_Delete();
GDirO* GDir();
//===============================================
#endif
//===============================================
