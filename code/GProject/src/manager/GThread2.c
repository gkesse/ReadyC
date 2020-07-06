//===============================================
#include "GThread2.h"
#include "GThread2.h"
#include "GThread2.h"
#include "GString3.h"
#include "GConfig.h"
//===============================================
static void GThread2_Create(char* threadName, void* onFunc, void* params);
static void GThread2_Join(char* threadName);
static void GThread2_Exit(char* threadName);
static void GThread2_BeginThread(char* threadName, void* onFunc, void* params);
static void GThread2_WaitForSingleObject(char* threadName, int delay);
static void GThread2_CloseHandle(char* threadName);
//===============================================
GThread2O* GThread2_New() {
    GThread2O* lObj = (GThread2O*)malloc(sizeof(GThread2O));
    lObj->m_child = 0;
	lObj->Create = GThread2_Create;
	lObj->Join = GThread2_Join;
	lObj->Exit = GThread2_Exit;
	lObj->BeginThread = GThread2_BeginThread;
	lObj->WaitForSingleObject = GThread2_WaitForSingleObject;
	lObj->CloseHandle = GThread2_CloseHandle;
    return lObj;
}
//===============================================
void GThread2_Delete(GThread2O* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GThread2O* GThread2() {
#if defined(__unix)
    return GThread2();
#endif
#if defined(__WIN32)
    return GThread2();
#endif
    return 0;
}
//===============================================
static void GThread2_Create(char* threadName, void* onFunc, void* params) {}
static void GThread2_Join(char* threadName) {}
static void GThread2_Exit(char* threadName) {}
static void GThread2_BeginThread(char* threadName, void* onFunc, void* params) {}
static void GThread2_WaitForSingleObject(char* threadName, int delay) {}
static void GThread2_CloseHandle(char* threadName) {}
//===============================================
