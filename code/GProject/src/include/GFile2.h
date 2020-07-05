//===============================================
#ifndef _GFile2_
#define _GFile2_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GFile2O GFile2O;
typedef struct _GMapO_GDBus_GCHAR_PTR_GFILE_PTR GMapO_GDBus_GCHAR_PTR_GFILE_PTR;
//===============================================
struct _GFile2O {
    void (*Delete)();
    void (*Exist)(char* file);
    void (*Open)(char* pFileName, char* file, char* mode);
    int (*Write)(char* pFileName, char* data, int size);
    int (*Read)(char* pFileName, char* data, int size);
    int (*Format)(FILE *stream, const char *format, ...);
    void (*Close)(char* pFileName);
	GMapO(GDBus_GCHAR_PTR_GFILE_PTR)* m_pFileMap;
};
//===============================================
GFile2O* GFile2_New();
void GFile2_Delete();
GFile2O* GFile2();
//===============================================
#endif
//===============================================
