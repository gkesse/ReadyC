//===============================================
#include "GProcessTimer.h"
//#include "GTimer2.h"
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <linux/limits.h>
#include <time.h>
#include <sys/signal.h>
#include <sys/errno.h>
//===============================================
static GProcessO* m_GProcessTimerO = 0;
//===============================================
static void GProcessTimer_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessTimer_New() {
	GProcessO* lParent = GProcess_New();
	GProcessTimerO* lChild = (GProcessTimerO*)malloc(sizeof(GProcessTimerO));

	lChild->m_parent = lParent;

	lParent->m_child = lChild;
	lParent->Delete = GProcessTimer_Delete;
	lParent->Run = GProcessTimer_Run;
	return lParent;
}
//===============================================
void GProcessTimer_Delete() {
	GProcess_Delete(m_GProcessTimerO);
	m_GProcessTimerO = 0;
}
//===============================================
GProcessO* GProcessTimer() {
	if(m_GProcessTimerO == 0) {
		m_GProcessTimerO = GProcessTimer_New();
	}
	return m_GProcessTimerO;
}
//===============================================
#define FAILURE -1
#define ABS_2     TIMER_ABSTIME
#define REL     0
#define TIMERS  3

#define MIN_2(x,y) (((x) < (y)) ? (x) : (y))

void sig_handler(int);
void timeaddval(struct timespec *, struct timespec *);
struct sigaction sig_act;

/*
 * Control Structure for Timer Examples
 */
struct timer_definitions {
	int type;                       /* ABS_2olute or Relative Timer */
	struct sigevent evp;            /* Event structure */
	struct itimerspec timeout;      /* Timer interval */
};

/*
 * Initialize timer_definitions array for use in example as follows:
 *
 *   type, { sigev_value, sigev_signo }, { it_iteration, it_value }
 */

struct timer_definitions timer_values[TIMERS] = {
		{ ABS_2, {0,SIGALRM}, {0,0, 3,0} },
		{ ABS_2, {0,SIGUSR1}, {0,500000000, 2,0} },
		{ REL, {0,SIGUSR2}, {0,0, 5,0} }
};

timer_t timerid[TIMERS];
int timers_available;                   /* number of timers available */
volatile int alrm, usr1, usr2;
sigset_t mask;
//===============================================
static void GProcessTimer_Run(int argc, char** argv) {
	int status, i;
	int clock_id = CLOCK_REALTIME;
	struct timespec current_time;

	/*
	 *  Initialize the sigaction structure for the handler.
	 */

	sigemptyset(&mask);
	sig_act.sa_handler = sig_handler;
	sig_act.sa_flags = 0;
	sigemptyset(&sig_act.sa_mask);
	alrm = usr1 = usr2 = 0;

	/*
	 *  DeterMIN_2e whether it's possible to create TIMERS timers.
	 *  If not, create TIMER_MAX timers.
	 */

	timers_available = MIN_2(sysconf(_SC_TIMER_MAX),TIMERS);

	/*
	 * Create "timer_available" timers, using a unique signal
	 * type to denote the timer's expiration. Then initialize
	 * a signal handler to handle timer expiration for the timer.
	 */

	for (i = 0; i < timers_available; i++) {
		status = timer_create(clock_id, &timer_values[i].evp,
				&timerid[i]);
		if (status == FAILURE) {
			perror("timer_create");
			exit(FAILURE);
		}
		sigaction(timer_values[i].evp.sigev_signo, &sig_act, 0);
	}

	/*
	 * Establish a handler to catch CTRL-c and use it for exiting.
	 */

	sigaction(SIGINT, &sig_act, NULL);      /* catch crtl-c */

	/*
	 * Queue the following Timers: (see timer_values structure for details)
	 *
	 *   1.  An ABS_2olute one shot timer  (Notification is via SIGALRM).
	 *   2.  An ABS_2olute periodic timer. (Notification is via SIGUSR1).
	 *   3.  A relative one shot timer.  (Notification is via SIGUSR2).
	 *
	 * (NOTE: The number of TIMERS queued actually depends on
	 *  timers_available)
	 */

	for (i = 0; i < timers_available; i++) {
		if (timer_values[i].type == ABS_2) {
			status = clock_gettime(CLOCK_REALTIME, &current_time);
			timeaddval(&timer_values[i].timeout.it_value,
					&current_time);
		}
		status = timer_settime(timerid[i], timer_values[i].type,
				&timer_values[i].timeout, NULL);
		if (status == FAILURE) {
			perror("timer_settime failed: ");
			exit(FAILURE);
		}
	}

	/*
	 * Loop forever.  The application will exit in the signal handler
	 * when a SIGINT is issued (CRTL/C will do this).
	 */

	for(;;) pause();
}
//===============================================
void sig_handler(int signo)
{
        int i, status;

        switch (signo) {
            case SIGALRM:
                alrm++;
                break;
            case SIGUSR1:
                usr1++;
                break;
            case SIGUSR2:
                usr2++;
                break;
            case SIGINT:
                for (i = 0; i < timers_available; i++)  /* delete timers */
                        status = timer_delete(timerid[i]);
                printf("ALRM: %d, USR1: %d, USR2: %d\n", alrm, usr1, usr2);
                exit(1);  /* exit if CRTL/C is issued */
        }
        return;
}

/*
 * Add two timevalues: t1 = t1 + t2
 */

void timeaddval(struct timespec* t1, struct timespec* t2)
{
        t1->tv_sec += t2->tv_sec;
        t1->tv_nsec += t2->tv_nsec;
        if (t1->tv_nsec < 0) {
                t1->tv_sec--;
                t1->tv_nsec += 1000000000;
        }
        if (t1->tv_nsec >= 1000000000) {
                t1->tv_sec++;
                t1->tv_nsec -= 1000000000;
        }
}
//===============================================
