//===============================================
#ifndef _GSemaphore_
#define _GSemaphore_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GSemaphoreO GSemaphoreO;
typedef struct _GMapO_GSemaphore_GCHAR_PTR_GSEM_PTR GMapO_GSemaphore_GCHAR_PTR_GSEM_PTR;
//===============================================
struct _GSemaphoreO {
    void (*Delete)();
    void (*MallocSem)(char* semName);
    void (*SemOpen)(char* semName, char* name, int oflag, int mode, int value);
    void (*SemWait)(char* semName);
    void (*SemPost)(char* semName);
    void (*FreeSem)(char* semName);
    GMapO(GSemaphore_GCHAR_PTR_GSEM_PTR)* m_semMap;
};
//===============================================
GSemaphoreO* GSemaphore_New();
void GSemaphore_Delete();
GSemaphoreO* GSemaphore();
//===============================================
#endif
//===============================================
