//===============================================
#include "GProcessTimerInterval.h"
//===============================================
static GProcessO* m_GProcessTimerIntervalO = 0;
//===============================================
static void GProcessTimerInterval_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessTimerInterval_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTimerIntervalO* lChild = (GProcessTimerIntervalO*)malloc(sizeof(GProcessTimerIntervalO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTimerInterval_Delete;
	lParent->Run = GProcessTimerInterval_Run;
	return lParent;
}
//===============================================
void GProcessTimerInterval_Delete() {
	GProcess_Delete(m_GProcessTimerIntervalO);
	m_GProcessTimerIntervalO = 0;
}
//===============================================
GProcessO* GProcessTimerInterval() {
	if(m_GProcessTimerIntervalO == 0) {
		m_GProcessTimerIntervalO = GProcessTimerInterval_New();
	}
	return m_GProcessTimerIntervalO;
}
//===============================================
static void GProcessTimerInterval_Run(int argc, char** argv) {
<<<<<<< HEAD

=======
    //===============================================
	/*
    alarm(5);
    signal(SIGALRM, GProcessTimerInterval_Handler);
    pause();
    */
    //===============================================
    struct itimerval tval;
	//timerclear(& tval.it_interval);	/* zero interval means no reset of timer */
	//timerclear(& tval.it_value);
	tval.it_value.tv_sec = 1;	/* 10 second timeout */
	signal(SIGALRM, GProcessTimerInterval_Handler);
	int lRes = setitimer(ITIMER_REAL, &tval, NULL);
    if(lRes == -1) {printf("Error...........\n"); exit(0);}
    pause();
}
//===============================================
static void GProcessTimerInterval_Handler(int signo) {
    printf("hellllllllllllllo\n");
>>>>>>> 5b7f192439d88d41b24cf3a5f45ddacfdff61604
}
//===============================================
