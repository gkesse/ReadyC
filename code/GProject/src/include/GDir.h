//===============================================
#ifndef _GDir_
#define _GDir_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDirO GDirO;
//===============================================
struct _GDirO {
	void (*Delete)();
	void (*Path)(const char* pathIn, char* pathOut);
	void (*PathC)(const char* pathIn, char* pathOut);
	void (*Name)(const char* pathIn, char* pathOut);
	void (*Create)(const char* pathIn);
    //===============================================
    char m_dataPath[256];
};
//===============================================
GDirO* GDir_New();
void GDir_Delete();
GDirO* GDir();
//===============================================
#endif
//===============================================
