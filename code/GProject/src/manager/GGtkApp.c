//===============================================
#include "GGtkApp.h"
#include "GGtkAppWin.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
struct _GGtkApp {
	GtkApplication parent;
};
//===============================================
struct _GGtkAppClass {
	GtkApplicationClass parent_class;
};
//===============================================
G_DEFINE_TYPE(GGtkApp, ggtk_app, GTK_TYPE_APPLICATION);
//===============================================
static void ggtk_app_init (GGtkApp *app) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
}
//===============================================
static void ggtk_app_activate (GApplication *app) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
	GGtkAppWin* lWindow = ggtk_app_win_new (GGTK_APP (app));
	gtk_window_present (GTK_WINDOW (lWindow));
}
//===============================================
static void ggtk_app_open (GApplication  *app, GFile **files, gint n_files, const gchar *hint) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
	GList* lWindows	= gtk_application_get_windows (GTK_APPLICATION (app));
	GGtkAppWin* lWindow = 0;
	if (lWindows) lWindow = GGTK_APP_WIN (lWindows->data);
	else lWindow = ggtk_app_win_new (GGTK_APP (app));
	for (int i = 0; i < n_files; i++) {
		ggtk_app_win_open (lWindow, files[i]);
	}
	gtk_window_present (GTK_WINDOW (lWindow));
}
//===============================================
static void ggtk_app_class_init (GGtkAppClass *class) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
	G_APPLICATION_CLASS (class)->activate = ggtk_app_activate;
	G_APPLICATION_CLASS (class)->open = ggtk_app_open;
}
//===============================================
GGtkApp* ggtk_app_new() {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
	return g_object_new (
			GGTK_APP_TYPE,
			"application-id", "org.readydev.gpc.desktop",
			"flags", G_APPLICATION_HANDLES_OPEN,
			NULL
	);
}
//===============================================
#endif
//===============================================
