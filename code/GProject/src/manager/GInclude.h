//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
/* Define */
#define _USE_MATH_DEFINES
#define _POSIX_C_SOURCE 200809L
//===============================================
/* C Standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//===============================================
/* SQLite */
#include <sqlite3.h>
//===============================================
#if defined(__WIN32)
#define G_PLATEFORM_OS "WINDOWS"
//===============================================
/* Socket */
#include <winsock2.h>
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
/* Timer */
//#include <time.h>
//===============================================
/* Signal */
//#include <signal.h>
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
#endif
//===============================================
/* Define */
#if !defined(TRUE)
#define FALSE (0)
#define TRUE (!FALSE)
#endif
//===============================================
/* Typedef */
typedef unsigned char uchar;
typedef unsigned int uint;
typedef unsigned long ulong;
typedef unsigned long int ulint;
//===============================================
#endif
//===============================================
