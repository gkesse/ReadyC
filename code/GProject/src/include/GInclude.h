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
<<<<<<< HEAD
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
=======
#define _GUSE_CCV_ON_
//===============================================
#if defined(_GUSE_CCV_ON_)
#include <ccv.h>
#endif
//===============================================
#endif
//===============================================
#elif defined(__WIN32)
//===============================================
#define _D_GNU_SOURCE
#define _USE_MATH_DEFINES 
>>>>>>> c70f04fa4527d8118859c8020c646a2ef7fa40e2
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
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
=======
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
>>>>>>> c70f04fa4527d8118859c8020c646a2ef7fa40e2
#endif
//===============================================
#if !defined(TRUE)
#define FALSE (0)
#define TRUE (!FALSE)
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
