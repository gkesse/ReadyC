//===============================================
#include "GProcessClock.h"
#include "GConfig.h"
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
	printf("=================================================\n");
	struct timespec     clock_resolution;
	int stat;

	stat = clock_getres(CLOCK_REALTIME, &clock_resolution);

	printf("Clock resolution is %ld seconds, %ld nanoseconds : %d\n",
			clock_resolution.tv_sec, clock_resolution.tv_nsec, stat);

	printf("=================================================\n");
	struct timespec ts;

	/* Call time */
	printf("time returns %ld seconds\n", time(NULL));
	/* Call clock_gettime */

	clock_gettime(CLOCK_REALTIME, &ts);
	printf("clock_gettime returns:\n");
	printf("%ld seconds and %ld nanoseconds\n", ts.tv_sec, ts.tv_nsec);
	printf("=================================================\n");
}
//===============================================
