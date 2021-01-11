//===============================================
#include "GOpenCV.h"
#include "GOpenCVUnix.h"
#include "GOpenCVWin.h"
#include "GManager.h"
//===============================================
static void GOpenCV_Test(int argc, char** argv);
static void GOpenCV_OnOpen();
static void GOpenCV_Init();
static void GOpenCV_Free();
static void GOpenCV_UpdateBgColor();
static void GOpenCV_LoadImage();
static void GOpenCV_ImageRatio();
//===============================================
GOpenCVO* GOpenCV_New() {
	GOpenCVO* lObj = (GOpenCVO*)malloc(sizeof(GOpenCVO));

	lObj->Delete = GOpenCV_Delete;
	lObj->Test = GOpenCV_Test;
	lObj->OnOpen = GOpenCV_OnOpen;
	lObj->Init = GOpenCV_Init;
	lObj->Free = GOpenCV_Free;
	lObj->UpdateBgColor = GOpenCV_UpdateBgColor;
	lObj->LoadImage = GOpenCV_LoadImage;
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
    
    GOpenCV()->Free();
}
//===============================================
static void GOpenCV_Init() {    
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;

    lOpenCV->win_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);
    lOpenCV->bg_img = cvCreateImage(cvSize(lOpenCV->win_width, lOpenCV->win_height), IPL_DEPTH_8U, 3);

    cvSet(lOpenCV->bg_img, lOpenCV->bg_color, 0);
    cvCopy(lOpenCV->bg_img, lOpenCV->win_img, 0);
}
//===============================================
static void GOpenCV_Free() {    
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;
    
    lOpenCV->state = "close";
    
    cvReleaseImage(&lOpenCV->win_img);
    cvReleaseImage(&lOpenCV->bg_img);
    
    cvDestroyWindow(lOpenCV->win_title);
}
//===============================================
static void GOpenCV_UpdateBgColor() {    
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;
    
    cvSet(lOpenCV->bg_img, lOpenCV->bg_color, 0);
    cvCopy(lOpenCV->bg_img, lOpenCV->win_img, 0);
}
//===============================================
static void GOpenCV_LoadImage() {    
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;
    
    if(lOpenCV->load_img) cvReleaseImage(&lOpenCV->load_img);
    
    lOpenCV->load_img = cvLoadImage(lOpenCV->load_img_file, CV_LOAD_IMAGE_COLOR);
    
    if(!lOpenCV->load_img) {
        printf("[error] GOpenCV_LoadImage\n");
        return;
    }
    
    GOpenCV_ImageRatio();
    
    lOpenCV->win_x = (lOpenCV->win_width - lOpenCV->ratio_img->width)/2;
    lOpenCV->win_y = (lOpenCV->win_height - lOpenCV->ratio_img->height)/2;
    
    lOpenCV->win_roi = cvRect(lOpenCV->win_x, lOpenCV->win_y, lOpenCV->ratio_img->width, lOpenCV->ratio_img->height);
    
    cvSetImageROI(lOpenCV->win_img, lOpenCV->win_roi);
    cvAddWeighted(lOpenCV->ratio_img, 1, lOpenCV->win_img, 0, 0, lOpenCV->win_img);
    cvResetImageROI(lOpenCV->win_img);
    
    GManager()->DataShow();
}
//===============================================
static void GOpenCV_ImageRatio() {
    sGOpenCV* lOpenCV = GManager()->m_mgr->opencv;

    int lImgW = lOpenCV->load_img->width;
    int lImgH = lOpenCV->load_img->height;

    int lRefW = lOpenCV->win_width;
    int lRefH = lOpenCV->win_height;
    
    int lOutW = (lImgW * lRefH)/lImgH;
    int lOutH = (lImgH * lRefW)/lImgW;

    if(lOutH < lRefH) {lOutW = lRefW;}
    else if(lOutH > lRefH) {lOutH = lRefH;}

    if(lOpenCV->ratio_img) cvReleaseImage(&lOpenCV->ratio_img);
    
    lOpenCV->ratio_img = cvCreateImage(cvSize(lOutW, lOutH), IPL_DEPTH_8U, 3);
    
    if(!lOpenCV->ratio_img) {
        printf("[error] GOpenCV_ImageRatio\n");
        return;
    }
    
    printf("[%d]\n", lImgW);
    printf("[%d]\n", lImgH);

    printf("[%d]\n", lRefW);
    printf("[%d]\n", lRefH);

    printf("[%d]\n", lOutW);
    printf("[%d]\n", lOutH);

    cvResize(lOpenCV->load_img, lOpenCV->ratio_img, CV_INTER_LINEAR);
}    
//===============================================
