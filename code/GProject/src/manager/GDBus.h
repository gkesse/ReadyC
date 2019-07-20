//===============================================
#ifndef _GDBus_
#define _GDBus_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GDBusO GDBusO;
typedef struct _GMapO_GDBus_GCHAR_PTR_GDBusCONNECTION_PTR GMapO_GDBus_GCHAR_PTR_GDBusCONNECTION_PTR;
//===============================================
struct _GDBusO {
    void (*Delete)();
    void (*Init)();
    void (*Connection)(char* connName, int type);
    GMapO(GDBus_GCHAR_PTR_GDBusCONNECTION_PTR)* m_connMap;
};
//===============================================
GDBusO* GDBus_New();
void GDBus_Delete();
GDBusO* GDBus();
//===============================================
#endif
//===============================================
