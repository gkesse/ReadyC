//===============================================
#include "GGtkApp.h"
#include "GGtkAppWin.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
struct _GGtkApp {
	GtkApplication* parent;
};
//===============================================
struct _GGtkAppClass {
	GtkApplicationClass parent_class;
};
//===============================================
G_DEFINE_TYPE(GGtkApp, ggtk_app, GTK_TYPE_APPLICATION);
//===============================================
static void ggtk_app_init(GGtkApp* app) {

}
//===============================================
static void ggtk_app_class_init (GGtkAppClass *class) {
	G_APPLICATION_CLASS(class)->activate = ggtk_app_activate;
	G_APPLICATION_CLASS(class)->open = ggtk_app_open;
}
//===============================================
static void ggtk_app_activate(GApplication* app) {
	GGtkAppWin* lWindow = ggtk_app_win_new(GGTK_APP(app));
	gtk_window_present(GTK_WINDOW(lWindow));
}
//===============================================
static void ggtk_app_open (GApplication* app, GFile **files, gint n_files, const gchar *hint) {
	GList* lWindows	= gtk_application_get_windows(GTK_APPLICATION(app));
	GGtkAppWin* lWindow = 0;

	if(lWindows) lWindow = GGTK_APP_WIN (lWindows->data);
	else lWindow = ggtk_app_win_new (GGTK_APP(app));

	for(int i = 0; i < n_files; i++) {
		ggtk_app_window_open(lWindow, files[i]);
	}

	gtk_window_present (GTK_WINDOW(lWindow));
}
//===============================================
GGtkApp* ggtk_app_new(void) {
	return g_object_new (
			GGTK_APP_TYPE,
			"application-id", "org.ggtkapp.desktop",
			"flags", G_APPLICATION_HANDLES_OPEN,
			NULL);
}
//===============================================
#endif
//===============================================
