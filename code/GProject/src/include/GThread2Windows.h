//===============================================
#ifndef _GThread2Windows_
#define _GThread2Windows_
//===============================================
#include "GThread2.h"
#include "GMap.h"
//===============================================
typedef struct _GThread2WindowsO GThread2WindowsO;
typedef struct _GMapO_GThread2Windows_GCHAR_PTR_GHANDLE_PTR GMapO_GThread2Windows_GCHAR_PTR_GHANDLE_PTR;
//===============================================
struct _GThread2WindowsO {
	void* m_parent;
#if defined(__WIN32)
	GMapO(GThread2Windows_GCHAR_PTR_GHANDLE_PTR)* m_threadMap;
#endif
};
//===============================================
GThread2O* GThread2Windows_New();
void GThread2Windows_Delete(GThread2O* obj);
GThread2O* GThread2Windows();
//===============================================
#endif
//===============================================
