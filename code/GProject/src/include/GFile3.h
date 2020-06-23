//===============================================
#ifndef _GFile3_
#define _GFile3_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GFile3O GFile3O;
typedef struct _GMapO_GFile3_GCHAR_PTR_GVOID_PTR GMapO_GFile3_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GFile3O { 
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
	GMapO_GFile3_GCHAR_PTR_GVOID_PTR* m_pFileMap;
};
//===============================================
GFile3O* GFile3_New();
void GFile3_Delete();
GFile3O* GFile3();
//===============================================
#endif
//===============================================
