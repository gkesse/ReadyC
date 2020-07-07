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
//===============================================
#include <windows.h>
#include <process.h>
#include <winsock2.h>
#include <conio.h>
//===============================================
#define _GUSE_SQLITE_ON_
#define _GUSE_MYSQL_ON_0
#define _GUSE_THREAD_ON_
//===============================================
#if defined(_GUSE_SQLITE_ON_)
#include <sqlite3.h>
#endif
//===============================================
#if defined(_GUSE_MYSQL_ON_)
#include <mysql/mysql.h>
#endif
//===============================================
#if defined(_GUSE_SQLITE_ON_)
#include <sqlite3.h>
#endif
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
#include <sys/time.h>
#include <setjmp.h>  
#include <sched.h>
#include <semaphore.h>
#include <pthread.h>
#include <netinet/in.h>
#include <netinet/tcp.h> 
#include <sys/socket.h>
//===============================================
#define _GUSE_GTK_ON_0
#define _GUSE_GSOAP_ON_0
#define _GUSE_DBUS_ON_
#define _GUSE_SQLITE_ON_
#define _GUSE_MYSQL_ON_0
#define _GUSE_SCHEDULER_ON_0
#define _GUSE_THREAD_ON_
//===============================================
#if defined(_GUSE_GTK_ON_)
#include <gtk/gtk.h>
#endif 
//===============================================
#if defined(_GUSE_GSOAP_ON_)
#include <stdsoap2.h>
#include <soapStub.h>
#endif
//===============================================
#if defined(_GUSE_DBUS_ON_)
#include <dbus/dbus.h>
#endif
//===============================================
#if defined(_GUSE_SQLITE_ON_)
#include <sqlite3.h>
#endif
//===============================================
#if defined(_GUSE_MYSQL_ON_)
#include <mysql.h>
#endif
//===============================================
#endif
//===============================================
#if !defined(TRUE)
#define FALSE (0)
#define TRUE (!FALSE)
#endif
//===============================================
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long int ulint;
//===============================================
#endif
//===============================================
