//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__CYGWIN__)
#define _GARCHI_CYGWIN_
#elif defined(__unix)
#define _GARCHI_UNIX_
#elif defined(__WIN32)
#define _GARCHI_WIN_
#endif
//===============================================
#if defined(__unix)
//===============================================
#define _GUSE_GTK_ON_
#define _GUSE_DBUS_ON_
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <stdint.h>
//===============================================
#if defined(_GUSE_GTK_ON_)
#include <gtk/gtk.h>
#endif
//===============================================
#if defined(_GUSE_DBUS_ON_)
#include <dbus/dbus.h>
#endif
//===============================================
#endif
//===============================================
#if defined(__WIN32)
//===============================================
#define _GUSE_GTK_ON_
#define _GUSE_DBUS_OFF_
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
#if defined(_GUSE_DBUS_ON_)
#include <dbus/dbus.h>
#endif
//===============================================
#endif
//===============================================
#include "GStruct.h"
//===============================================
#endif
//===============================================
