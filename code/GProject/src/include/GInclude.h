//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__WIN32)
//===============================================
#define _GPLATEFOME_ "WINDOWS"
//===============================================
#define _GUSE_GTK_ON_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
//===============================================
#if defined(_GUSE_GTK_ON_)
#include <gtk/gtk.h>
#include <gio/gio.h>
#endif
//===============================================
#endif
//===============================================
#include "GStruct.h"
//===============================================
#endif
//===============================================