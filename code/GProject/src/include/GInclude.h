//===============================================
#ifndef _GInclude_
#define _GInclude_
 //===============================================
#if defined(__WIN32)
//===============================================
#define G_PLATEFORM_OS "WINDOWS"
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <stdarg.h>
//===============================================
#include <windows.h>
#include <process.h>
#include <winsock2.h>
//===============================================
#define _GUSE_SQLITE_ON_
//===============================================
#if defined(_GUSE_SQLITE_ON_)
#include <sqlite3.h>
#endif
//===============================================
#elif defined(__unix)
//===============================================
#define G_PLATEFORM_OS "UNIX"
//===============================================
#define _GNU_SOURCE
#define _USE_MATH_DEFINES
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//===============================================
#include <errno.h>  
#include <sys/time.h>
#include <signal.h>  
#include <setjmp.h>  
#include <sched.h>
#include <semaphore.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
//===============================================
#include <gtk/gtk.h>
#include <sqlite3.h>
#include <dbus/dbus.h>
#include <stdsoap2.h>
#include <soapStub.h>
#include <mysql/mysql.h>
//===============================================
#endif
//===============================================
#if !defined(TRUE)
#define FALSE (0)
#define TRUE (!FALSE)
#endif
//===============================================
#if !defined(BOOL)
#define BOOL int
#endif
//===============================================
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long int ulint;
//===============================================
#endif
//===============================================
