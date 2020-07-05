//===============================================
#ifndef _GGtkAppWin_
#define _GGtkAppWin_
//===============================================
#include "GInclude.h"
#include "GGtkApp.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
#define GGTK_APP_WIN_TYPE (ggtk_app_win_get_type ())
#define GGTK_APP_WIN(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GGTK_APP_WIN_TYPE, GGtkAppWin))
//===============================================
typedef struct _GGtkAppWin GGtkAppWin;
typedef struct _GGtkAppWinClass GGtkAppWinClass;
//===============================================
GType ggtk_app_win_get_type();
GGtkAppWin* ggtk_app_win_new(GGtkApp *app);
void ggtk_app_win_open(GGtkAppWin *win, GFile* file);
//===============================================
#endif
//===============================================
#endif
//===============================================
