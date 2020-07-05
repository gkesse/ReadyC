//===============================================
#ifndef _GClock_
#define _GClock_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GClockO GClockO;
typedef struct _GMapO_GClock_GCHAR_PTR_GVOID_PTR GMapO_GClock_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GClockO {
    void (*Delete)();
    void (*Start)(char* clockId);
    void (*End)(char* clockId);
    double (*Time)(char* clockId);
    //===============================================
    GMapO_GClock_GCHAR_PTR_GVOID_PTR* m_startMap; 
    GMapO_GClock_GCHAR_PTR_GVOID_PTR* m_endMap; 
};
//===============================================
GClockO* GClock_New();
void GClock_Delete();
GClockO* GClock();
//===============================================
#endif
//===============================================
