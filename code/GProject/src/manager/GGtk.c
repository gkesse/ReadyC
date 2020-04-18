//===============================================
#include "GGtk.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Test(int argc, char** argv);
//===============================================
static void GGtk_OnStartup (GApplication *app);
static void GGtk_OnActivate (GApplication *app);
static void GGtk_Default (GApplication *app);
static void GGtk_Button(GApplication *app);
//===============================================
GGtkO* GGtk_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GGtkO* lObj = (GGtkO*)malloc(sizeof(GGtkO));

	lObj->m_argMap = (sGArgMap*)malloc(sizeof(sGArgMap));

	lObj->Delete = GGtk_Delete;
	lObj->Test = GGtk_Test;
	return lObj;
}
//===============================================
void GGtk_Delete() {
	GDebug()->Write(__FUNCTION__, 0);
	GGtkO* lObj = GGtk();
	free(lObj);
	m_GGtkO = 0;
}
//===============================================
GGtkO* GGtk() {
	if(m_GGtkO == 0) {
		m_GGtkO = GGtk_New();
	}
	return m_GGtkO;
}
//===============================================
static void GGtk_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);

	gtk_init(&argc, &argv);
	GtkApplication* lApp = gtk_application_new ("org.gtk.example", G_APPLICATION_FLAGS_NONE);

	m_GGtkO->m_argMap->argc = argc;
	m_GGtkO->m_argMap->argv = argv;

	g_signal_connect(lApp, "startup", G_CALLBACK (GGtk_OnStartup), NULL);
	g_signal_connect(lApp, "activate", G_CALLBACK (GGtk_OnActivate), NULL);

	g_application_run (G_APPLICATION(lApp), 0, 0);
	g_object_unref (G_APPLICATION(lApp));
}
//===============================================
static void GGtk_OnStartup(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnActivate(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
	int lArgc = m_GGtkO->m_argMap->argc;
	char** lArgv = m_GGtkO->m_argMap->argv;
	int lRunFlag = 0;
	for(int i = 2; i < lArgc;) {
		char* lKey = lArgv[i++];
		if(strcmp(lKey, "button") == 0) {
			GGtk_Button(app); lRunFlag = 1; break;
		}
		break;
	}
	if(lRunFlag == 0) GGtk_Default(app);
}
//===============================================
static void GGtk_Default(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
	GtkWidget* lWindow = gtk_application_window_new(G_APPLICATION(app));
	gtk_window_set_title (GTK_WINDOW(lWindow), "Gtk | ReadyDev");
	gtk_window_set_default_size (GTK_WINDOW(lWindow), 640, 480);
	gtk_widget_show_all(lWindow);
}
//===============================================
static void GGtk_Button(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
	GtkWidget* lWindow = gtk_application_window_new(G_APPLICATION(app));
	gtk_window_set_title (GTK_WINDOW(lWindow), "Gtk | ReadyDev");
	gtk_window_set_default_size (GTK_WINDOW(lWindow), 640, 480);

	GtkWidget* lButtonBox = gtk_button_box_new(GTK_ORIENTATION_HORIZONTAL);
	GtkWidget* lButton = gtk_button_new_with_label("Quitter");

	gtk_container_add(GTK_CONTAINER(lButtonBox), lButton);
	gtk_container_add(GTK_CONTAINER(lWindow), lButtonBox);

	gtk_widget_show_all(lWindow);
}
//===============================================
#endif
//===============================================
