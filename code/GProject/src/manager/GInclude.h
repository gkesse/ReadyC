//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
/* C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//===============================================
/* Socket */
#if defined(__WIN32)
#define G_PLATEFORM_OS "WINDOWS"
#include <winsock2.h>
#elif defined(__unix)
#define G_PLATEFORM_OS "UNIX"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <strings.h>
#endif
//===============================================
/* SQLite */
#include <sqlite3.h>
//===============================================
/* Gtk */
#include <gtk/gtk.h>
//===============================================
/* Soap */
<<<<<<< HEAD
#include <stdsoap2.h>
=======
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
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
//===============================================
#endif
//===============================================
