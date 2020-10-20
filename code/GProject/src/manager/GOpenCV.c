//===============================================
#include "GOpenCV.h"
#include "GManager.h"
//===============================================
#if defined(_GUSE_OPENCV_ON_)
//===============================================
static GOpenCVO* m_GOpenCVO = 0;
//===============================================
static void GOpenCV_Test(int argc, char** argv);
static void GOpenCV_Open();
static void GOpenCV_Close();
//===============================================
DWORD WINAPI GOpenCV_OnOpen(LPVOID params);
//===============================================
GOpenCVO* GOpenCV_New() {
	GOpenCVO* lObj = (GOpenCVO*)malloc(sizeof(GOpenCVO));

	lObj->Delete = GOpenCV_Delete;
	lObj->Test = GOpenCV_Test;
	lObj->Open = GOpenCV_Open;
	lObj->Close = GOpenCV_Close;
	return lObj;
}
//===============================================
void GOpenCV_Delete() {
    GOpenCVO* lObj = GOpenCV();
    if(lObj != 0) {
        free(lObj);
    }
    m_GOpenCVO = 0;
}
//===============================================
GOpenCVO* GOpenCV() {
	if(m_GOpenCVO == 0) {
		m_GOpenCVO = GOpenCV_New();
	}
	return m_GOpenCVO;
}
//===============================================
static void GOpenCV_Test(int argc, char** argv) {
    IplImage *img = cvLoadImage("box.png", 1);
    cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1", img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("Example1");
}
//===============================================
static void GOpenCV_Open() {
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;
    
    lOpenCV->win_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);
    lOpenCV->bg_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);

    cvSet(lOpenCV->bg_img, lOpenCV->bg_color, 0);
    cvCopy(lOpenCV->bg_img, lOpenCV->win_img, 0);

    cvNamedWindow(lOpenCV->win_title, CV_WINDOW_AUTOSIZE);

    HANDLE lAns = CreateThread(0, 0, GOpenCV_OnOpen, 0, 0, &lOpenCV->thread_id);
    
    if(!lAns) {
        GManager()->Trace(3, "[error] GOpenCV_Open : CreateThread", 0);
    }
}
//===============================================
DWORD WINAPI GOpenCV_OnOpen(LPVOID params) {    
    while(1) {
        if(lOpenCV->run_me == 0) break;
        cvShowImage(lOpenCV->win_title, lOpenCV->win_img);
        int lKey = cvWaitKey(lOpenCV->delay);
        if(lKey == 'q') break;
    }
    
    cvReleaseImage(&lOpenCV->img_bg);
    cvDestroyWindow(lOpenCV->win_title);
    return 0;
}
//===============================================
static void GOpenCV_Close() {
    IplImage *img = cvLoadImage("box.png", 1);
    cvNamedWindow("Example1", CV_WINDOW_AUTOSIZE);
    cvShowImage("Example1", img);
    cvWaitKey(0);
    cvReleaseImage(&img);
    cvDestroyWindow("Example1");
}
//===============================================
#endif
//===============================================
