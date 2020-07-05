//===============================================
#ifndef _GSQLite2_
#define _GSQLite2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLite2O GSQLite2O;
typedef struct _GMapO_GSQLite2_GCHAR_PTR_GVOID_PTR GMapO_GSQLite2_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GSQLite2O {
    void (*Delete)();
    void (*Version)();
    void (*Open)(char* dbId, char* path);
    //===============================================
    GMapO_GSQLite2_GCHAR_PTR_GVOID_PTR* m_dbMap; 
};
//===============================================
GSQLite2O* GSQLite2_New();
void GSQLite2_Delete();
GSQLite2O* GSQLite2();
//===============================================
#endif
//===============================================
