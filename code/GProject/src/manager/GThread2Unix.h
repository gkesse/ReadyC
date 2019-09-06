//===============================================
#ifndef _GThread2Unix_
#define _GThread2Unix_
//===============================================
#include "GThread2.h"
#include "GMap.h"
//===============================================
typedef struct _GThread2UnixO GThread2UnixO;
typedef struct _GMapO_GThread2Unix_GCHAR_PTR_GPTHREADT_PTR GMapO_GThread2Unix_GCHAR_PTR_GPTHREADT_PTR;
//===============================================
struct _GThread2UnixO {
	void* m_parent;
#if defined(__unix)
	GMapO(GThread2Unix_GCHAR_PTR_GPTHREADT_PTR)* m_threadMap;
#endif
};
//===============================================
GThread2UnixO* GThread2Unix_New();
void GThread2Unix_Delete();
GThread2UnixO* GThread2Unix();
//===============================================
#endif
//===============================================
