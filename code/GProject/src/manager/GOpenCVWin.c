//===============================================
#include "GOpenCVWin.h"
#include "GManager.h"
//===============================================
#if defined(__unix)
//===============================================
static GOpenCVO* m_GOpenCVWinO = 0;
//===============================================
static void GOpenCVWin_Open();
static DWORD WINAPI GOpenCV_OnOpen(LPVOID params);
//===============================================
GOpenCVO* GOpenCVWin_New() {
	GOpenCVO* lParent = GOpenCV_New();
	GOpenCVWinO* lChild = (GOpenCVWinO*)malloc(sizeof(GOpenCVWinO));
    
    lChild->parent = lParent;

    lParent->child = lChild;
	lParent->Delete = GOpenCVWin_Delete;
	lParent->Open = GOpenCVWin_Open;
	return lParent;
}
//===============================================
void GOpenCVWin_Delete() {
    GOpenCV_Delete();
    m_GOpenCVWinO = 0;
}
//===============================================
GOpenCVO* GOpenCVWin() {
	if(m_GOpenCVWinO == 0) {
		m_GOpenCVWinO = GOpenCVWin_New();
	}
	return m_GOpenCVWinO;
}
//===============================================
static void GOpenCVWin_Open() {
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;

    lOpenCV->win_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);
    lOpenCV->bg_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);

    cvSet(lOpenCV->bg_img, lOpenCV->bg_color, 0);
    cvCopy(lOpenCV->bg_img, lOpenCV->win_img, 0);
    
    HANDLE lAns = CreateThread(0, 0, GOpenCV_OnOpen, 0, 0, &lOpenCV->thread_id);
    
    if(!lAns) {
        GManager()->Trace(3, "[error] GOpenCV_Open : CreateThread", 0);
    }
}
//===============================================
static DWORD WINAPI GOpenCV_OnOpen(LPVOID params) {    
    m_GOpenCVWinO->OnOpen();
    return 0;
}
//===============================================
#endif
//===============================================
