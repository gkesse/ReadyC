//===============================================
#ifndef _GFile_
#define _GFile_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GFileO GFileO;
typedef struct _GMapO_GFile_GCHAR_PTR_GVOID_PTR GMapO_GFile_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GFileO { 
	void (*Delete)();
	void (*Test)(int argc, char** argv);
	void (*Exist)(char* filename);
	void (*Open)(char* fileId, char* filename, char* mode);
	char* (*GetData)(char* fileId);
	void (*GetDataMap)(char* fileId);
	void (*GetDataCsv)(char* fileId);
	int (*Size)(char* fileId);
	void (*Show)(char* fileId);
	void (*Close)(char* fileId);
    //===============================================
	GMapO_GFile_GCHAR_PTR_GVOID_PTR* m_pFileMap;
};
//===============================================
GFileO* GFile_New();
void GFile_Delete();
GFileO* GFile();
//===============================================
#endif
//===============================================
