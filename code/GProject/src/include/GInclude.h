//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__WIN32)
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include <signal.h>
#include <windows.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
//===============================================
#elif defined(__unix)
//===============================================
#define _GNU_SOURCE
#define _USE_MATH_DEFINES
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
#include <signal.h>  
//===============================================
#include <unistd.h>  
#include <errno.h>  
#include <setjmp.h>  
#include <sched.h>
#include <semaphore.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
//===============================================
#include <sqlite3.h>
//===============================================
#endif
//===============================================
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long int ulint;
//===============================================
#endif
//===============================================
