//===============================================
#include "GProcessClock.h"
#include "GClock.h"
#include "GLog.h"
//===============================================
static GProcessO* m_GProcessClockO = 0;
//===============================================
static void GProcessClock_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessClock_New() {
	GProcessO* lParent = GProcess_New();
	GProcessClockO* lChild = (GProcessClockO*)malloc(sizeof(GProcessClockO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessClock_Delete;
	lParent->Run = GProcessClock_Run;
	return lParent;
}
//===============================================
void GProcessClock_Delete() {
	GProcess_Delete(m_GProcessClockO);
	m_GProcessClockO = 0;
}
//===============================================
GProcessO* GProcessClock() {
	if(m_GProcessClockO == 0) {
		m_GProcessClockO = GProcessClock_New();
	}
	return m_GProcessClockO;
}
//===============================================
static void GProcessClock_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessClock_Run");
    //GLog()->Write("#================================================");
	printf("=================================================\n");
    long lClock = GClock()->GetClock();
    long lClockPerSec = GClock()->GetClockPerSec();
    printf("%-20s : %ld\n", "lClock", lClock);
    printf("%-20s : %ld\n", "lClockPerSec", lClockPerSec);
	printf("=================================================\n");
    long lClockT1 = GClock()->GetClock();
    
    long lCompute = 0;
    for(long i = 0; i < 1000000000; i++) {lCompute++;}
    printf("%-20s : %ld\n", "lCompute", lCompute);
    
    long lClockT2 = GClock()->GetClock();
    long lClockDT = lClockT2 - lClockT1;
    double lSecond = GClock()->GetSecond(lClockDT);
    printf("%-20s : %ld\n", "lClockT1", lClockT1);
    printf("%-20s : %ld\n", "lClockT2", lClockT2);
    printf("%-20s : %ld\n", "lClockDT", lClockDT);
    printf("%-20s : %.2f\n", "lSecond", lSecond);
	printf("=================================================\n");
}
//===============================================
