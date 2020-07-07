//===============================================
#include "GThread2.h"
#include "GThread2Unix.h"
#include "GThread2Win.h"
#include "GString3.h"
#include "GConfig.h"
//===============================================
#if defined(_GUSE_THREAD_ON_)
//===============================================
static void GThread2_Create(char* threadId, void* onFunc, void* params);
static void GThread2_Join(char* threadId, int delay);
static void GThread2_Close(char* threadId);
//===============================================
GThread2O* GThread2_New() {
    GThread2O* lObj = (GThread2O*)malloc(sizeof(GThread2O));
    lObj->m_child = 0;
	lObj->Create = GThread2_Create;
	lObj->Join = GThread2_Join;
	lObj->Close = GThread2_Close;
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
    return GThread2Unix();
#endif
#if defined(__WIN32)
    return GThread2Win();
#endif
    return 0;
}
//===============================================
static void GThread2_Create(char* threadId, void* onFunc, void* params) {}
static void GThread2_Join(char* threadId, int delay) {}
static void GThread2_Close(char* threadId) {}
//===============================================
#endif
//===============================================
