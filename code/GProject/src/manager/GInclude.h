//===============================================
#ifndef _GInclude_
#define _GInclude_
 //===============================================
#if defined(__MINGW32__)
#define G_PLATEFORM_OS "WINDOWS"
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//===============================================
#include <windows.h>
#include <process.h>
#include <winsock2.h>
//===============================================
#include <sqlite3.h>
#include <argtable3.h>
//===============================================
#elif defined(__unix)
#define G_PLATEFORM_OS "UNIX"
//===============================================
/* Standard */
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
//===============================================
/* Signal */
#include <signal.h>
#include <setjmp.h>
//===============================================
/* Socket */
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
//===============================================
/* Thread */
#include <pthread.h>
//===============================================
/* Semaphore */
#include <semaphore.h>
//===============================================
/* Timer */
#include <sys/time.h>
//===============================================
/* MySQL */
#include <mysql.h>
//===============================================
/* Gtk */
#include <gtk/gtk.h> 
//===============================================
/* Soap */
#include <stdsoap2.h>
//===============================================
/* DBus */
#include <dbus/dbus.h>
//===============================================
/* ArgTable */
#include <argtable3.h>
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
