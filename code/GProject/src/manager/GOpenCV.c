//===============================================
#include "GOpenCV.h"
#include "GOpenCVUnix.h"
#include "GOpenCVWin.h"
#include "GManager.h"
//===============================================
static void GOpenCV_Test(int argc, char** argv);
static void GOpenCV_OnOpen();
//===============================================
GOpenCVO* GOpenCV_New() {
	GOpenCVO* lObj = (GOpenCVO*)malloc(sizeof(GOpenCVO));

	lObj->Delete = GOpenCV_Delete;
	lObj->Test = GOpenCV_Test;
	lObj->OnOpen = GOpenCV_OnOpen;
	return lObj;
}
//===============================================
void GOpenCV_Delete() {
    GOpenCVO* lObj = GOpenCV();
    if(lObj != 0) {
        free(lObj);
    }
}
//===============================================
GOpenCVO* GOpenCV() {
#if defined(__unix)
    return GOpenCVUnix();
#elif defined(__WIN32)
    return GOpenCVWin();
#endif
	return 0;
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
static void GOpenCV_OnOpen() {    
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;

    cvNamedWindow(lOpenCV->win_title, CV_WINDOW_AUTOSIZE);

    while(1) {
        if(lOpenCV->run_me == 0) break;
        cvShowImage(lOpenCV->win_title, lOpenCV->win_img);
        int lKey = cvWaitKey(lOpenCV->delay);
        if(lKey == 'q') break;
    }
    
    cvReleaseImage(&lOpenCV->win_img);
    cvReleaseImage(&lOpenCV->bg_img);
    cvDestroyWindow(lOpenCV->win_title);
}
//===============================================
