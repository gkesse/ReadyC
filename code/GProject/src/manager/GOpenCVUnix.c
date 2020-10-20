//===============================================
#include "GOpenCVUnix.h"
#include "GManager.h"
//===============================================
#if defined(__unix)
//===============================================
static GOpenCVO* m_GOpenCVUnixO = 0;
//===============================================
static void GOpenCVUnix_Open();
static void* GOpenCVUnix_OnOpen(void* params);
//===============================================
GOpenCVO* GOpenCVUnix_New() {
	GOpenCVO* lParent = GOpenCV_New();
	GOpenCVUnixO* lChild = (GOpenCVUnixO*)malloc(sizeof(GOpenCVUnixO));
    
    lChild->parent = lParent;

    lParent->child = lChild;
	lParent->Delete = GOpenCVUnix_Delete;
	lParent->Open = GOpenCVUnix_Open;
	return lParent;
}
//===============================================
void GOpenCVUnix_Delete() {
    GOpenCV_Delete();
    m_GOpenCVUnixO = 0;
}
//===============================================
GOpenCVO* GOpenCVUnix() {
	if(m_GOpenCVUnixO == 0) {
		m_GOpenCVUnixO = GOpenCVUnix_New();
	}
	return m_GOpenCVUnixO;
}
//===============================================
static void GOpenCVUnix_Open() {
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;

    lOpenCV->win_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);
    lOpenCV->bg_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);

    cvSet(lOpenCV->bg_img, lOpenCV->bg_color, 0);
    cvCopy(lOpenCV->bg_img, lOpenCV->win_img, 0);
    
    int lAns = pthread_create(&lOpenCV->thread_id, 0, GOpenCVUnix_OnOpen, 0);
    
    if(lAns) {
        GManager()->Trace(3, "[error] GOpenCVUnix_Open : pthread_create", 0);
    }
}
//===============================================
static void* GOpenCVUnix_OnOpen(void* params) {    
    m_GOpenCVUnixO->OnOpen();
    return 0;
}
//===============================================
#endif
//===============================================
