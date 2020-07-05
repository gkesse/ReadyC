//===============================================
#ifndef _GGtkApp_
#define _GGtkApp_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
#define GGTK_APP_TYPE (ggtk_app_get_type ())
#define GGTK_APP(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GGTK_APP_TYPE, GGtkApp))
//===============================================
typedef struct _GGtkApp GGtkApp;
typedef struct _GGtkAppClass GGtkAppClass;
//===============================================
GType ggtk_app_get_type();
GGtkApp* ggtk_app_new();
//===============================================
#endif
//===============================================
#endif
//===============================================
