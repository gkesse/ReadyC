//===============================================
#ifndef _GDir2_
#define _GDir2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDir2O GDir2O;
//===============================================
struct _GDir2O {
	void (*Delete)();
	void (*Path)(const char* pathIn, char* pathOut);
	void (*PathC)(const char* pathIn, char* pathOut);
	void (*Name)(const char* pathIn, char* pathOut);
	void (*Create)(const char* pathIn);
    //===============================================
    char m_dataPath[256];
};
//===============================================
GDir2O* GDir2_New();
void GDir2_Delete();
GDir2O* GDir2();
//===============================================
#endif
//===============================================
