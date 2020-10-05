//===============================================
#include "GOpenCV.h"
#include "GManager.h"
//===============================================
#if defined(_GUSE_OPENCV_ON_)
//===============================================
static GOpenCVO* m_GOpenCVO = 0;
//===============================================
static void GOpenCV_Test(int argc, char** argv);
//===============================================
GOpenCVO* GOpenCV_New() {
	GOpenCVO* lObj = (GOpenCVO*)malloc(sizeof(GOpenCVO));

	lObj->Delete = GOpenCV_Delete;
	lObj->Test = GOpenCV_Test;
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
#endif
//===============================================
