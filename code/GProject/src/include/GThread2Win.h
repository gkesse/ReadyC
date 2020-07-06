//===============================================
#ifndef _GThread2Win_
#define _GThread2Win_
//===============================================
#include "GThread2.h"
#include "GMap.h"
//===============================================
#if defined(__WIN32)
//===============================================
typedef struct _GThread2WinO GThread2WinO;
typedef struct _GMapO_GThread2Win_GCHAR_PTR_GVOID_PTR GMapO_GThread2Win_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GThread2WinO {
	void* m_parent;
	GMapO_GThread2Win_GCHAR_PTR_GVOID_PTR* m_threadMap;
};
//===============================================
GThread2O* GThread2Win_New();
void GThread2Win_Delete(GThread2O* obj);
GThread2O* GThread2Win();
//===============================================
#endif
//===============================================
#endif
//===============================================
