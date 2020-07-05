//===============================================
#ifndef _GMutex2_
#define _GMutex2_
//===============================================
#include "GInclude.h"
#include "GMap.h"
//===============================================
typedef struct _GMutex2O GMutex2O;
typedef struct _GMapO_GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR GMapO_GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR;
typedef struct _GMapO_GMutex2_GCHAR_PTR_GPTHREADATTR_PTR GMapO_GMutex2_GCHAR_PTR_GPTHREADATTR_PTR;
//===============================================
typedef enum _GMUTEX2_INITIALIZER {
	GMUTEX2_INIT_PTHREAD_MUTEX_INITIALIZER
} GMUTEX2_INITIALIZER;
//===============================================
struct _GMutex2O {
	void (*Delete)();
	void (*MallocThreadMutex)(char* threadMutexName);
	void (*InitThreadMutex)(char* threadMutexName, int threadMutex);
	void (*MutexLock)(char* threadMutexName);
	void (*MutexUnlock)(char* threadMutexName);
	void (*FreeThreadMutex)(char* threadMutexName);
#if defined(__unix)
	GMapO(GMutex2_GCHAR_PTR_GPTHREADMUTEX_PTR)* m_threadMutexMap;
	GMapO(GMutex2_GCHAR_PTR_GPTHREADATTR_PTR)* m_threadAttrMap;
#endif
};
//===============================================
GMutex2O* GMutex2_New();
void GMutex2_Delete();
GMutex2O* GMutex2();
//===============================================
#endif
//===============================================
