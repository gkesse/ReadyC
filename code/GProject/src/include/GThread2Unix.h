//===============================================
#ifndef _GThread2Unix_
#define _GThread2Unix_
//===============================================
#include "GThread2.h"
//===============================================
typedef struct _GThread2UnixO GThread2UnixO;
typedef struct _GMapO_GThread2Unix_GCHAR_PTR_GVOID_PTR GMapO_GThread2Unix_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GThread2UnixO {
	void* m_parent;
	GMapO_GThread2Unix_GCHAR_PTR_GVOID_PTR* m_threadMap;
};
//===============================================
GThread2O* GThread2Unix_New();
void GThread2Unix_Delete(GThread2O* obj);
GThread2O* GThread2Unix();
//===============================================
#endif
//===============================================
