//===============================================
#include "GGtkAppWin.h"
#include "GGtkApp.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
struct _GGtkAppWin {
	GtkApplicationWindow parent;
};
//===============================================
struct _GGtkAppWinClass {
	GtkApplicationWindowClass parent_class;
};
//===============================================
G_DEFINE_TYPE(GGtkAppWin, ggtk_app_win, GTK_TYPE_APPLICATION_WINDOW);
//===============================================
static void ggtk_app_win_init (GGtkAppWin *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void ggtk_app_win_class_init (GGtkAppWinClass *class) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
GGtkAppWin* ggtk_app_win_new (GGtkApp *app) {
	GDebug()->Write(__FUNCTION__, 0);
	return g_object_new (GGTK_APP_WIN_TYPE, "application", app, NULL);
}
//===============================================
void ggtk_app_win_open (GGtkAppWin *win, GFile *file) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
#endif
//===============================================
