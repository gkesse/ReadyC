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
	GDebug()->Write(1, __FUNCTION__, _EOA_);
}
//===============================================
static void ggtk_app_win_class_init (GGtkAppWinClass *class) {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
}
//===============================================
GGtkAppWin* ggtk_app_win_new (GGtkApp *app) {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
	return g_object_new (GGTK_APP_WIN_TYPE, "application", app, NULL);
}
//===============================================
void ggtk_app_win_open (GGtkAppWin *win, GFile *file) {
	GDebug()->Write(1, __FUNCTION__, _EOA_);
}
//===============================================
#endif
//===============================================
