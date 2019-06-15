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
#include <winsock2.h>
#define G_PLATEFORM_OS "WINDOWS"
#elif defined(__unix)
#define G_PLATEFORM_OS "UNIX"
#endif
//===============================================
/* SQLite */
#include <sqlite3.h>
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
