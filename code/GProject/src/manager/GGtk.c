//===============================================
#include "GGtk.h"
#include "GGtkApp.h"
#include "GDir2.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Test(int argc, char** argv);
static void GGtk_Code(int argc, char** argv);
static void GGtk_Builder(int argc, char** argv);
static void GGtk_Application(int argc, char** argv);
//===============================================
static void GGtk_BuilderPath (GGtkO* obj);
//===============================================
static void GGtk_OnStartup (GApplication *app);
static void GGtk_OnActivate (GApplication *app);
static void GGtk_OnQuit(GApplication *app);
static void GGtk_OnRun(GApplication *app);
static void GGtk_OnCreate(GApplication *app);
static void GGtk_OnRead(GApplication *app);
static void GGtk_OnUpdate(GApplication *app);
static void GGtk_OnDelete(GApplication *app);
//===============================================
static void GGtk_Default (GApplication *app);
static void GGtk_Button(GApplication *app);
static void GGtk_Grid(GApplication *app);
//===============================================
GGtkO* GGtk_New() {
	GDebug()->Write(__FUNCTION__, 0);
	GGtkO* lObj = (GGtkO*)malloc(sizeof(GGtkO));

	lObj->m_argMap = (sGArgMap*)malloc(sizeof(sGArgMap));
	GGtk_BuilderPath(lObj);

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
	int lRunFlag = 0;
	for(int i = 2; i < argc;) {
		char* lKey = argv[i++];
		if(strcmp(lKey, "builder") == 0) {
			GGtk_Builder(argc, argv); lRunFlag = 1; break;
		}
		if(strcmp(lKey, "app") == 0) {
			GGtk_Application(argc, argv); lRunFlag = 1; break;
		}
		break;
	}
	if(lRunFlag == 0) GGtk_Code(argc, argv);
}
//===============================================
static void GGtk_Code(int argc, char** argv) {
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
static void GGtk_Builder(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	gtk_init(&argc, &argv);

	GtkBuilder* lBuilder = gtk_builder_new ();
	GError* lError = 0;

	gtk_builder_add_from_file (lBuilder, m_GGtkO->m_builderPath, &lError);
	if(lError != 0) {printf("%s\n", lError->message); exit(0);}

	GObject* lWindow = gtk_builder_get_object (lBuilder, "window");
	GObject* lCreate = gtk_builder_get_object (lBuilder, "create");
	GObject* lRead = gtk_builder_get_object (lBuilder, "read");
	GObject* lUpdate = gtk_builder_get_object (lBuilder, "update");
	GObject* lDelete = gtk_builder_get_object (lBuilder, "delete");
	GObject* lRun = gtk_builder_get_object (lBuilder, "run");

	g_signal_connect (lWindow, "destroy", G_CALLBACK (gtk_main_quit), NULL);
	g_signal_connect (lCreate, "clicked", G_CALLBACK (GGtk_OnCreate), NULL);
	g_signal_connect (lRead, "clicked", G_CALLBACK (GGtk_OnRead), NULL);
	g_signal_connect (lUpdate, "clicked", G_CALLBACK (GGtk_OnUpdate), NULL);
	g_signal_connect (lDelete, "clicked", G_CALLBACK (GGtk_OnDelete), NULL);
	g_signal_connect (lRun, "clicked", G_CALLBACK (GGtk_OnRun), NULL);

	gtk_main ();
}
//===============================================
static void GGtk_Application(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, 0);
	g_application_run (G_APPLICATION (ggtk_app_new ()), argc, argv);
}
//===============================================
static void GGtk_BuilderPath (GGtkO* obj) {
	GDebug()->Write(__FUNCTION__, 0);
	char* lDataPath = GDir2()->m_dataPath;
	sprintf(obj->m_builderPath, "%s/%s", lDataPath, "data/builder/builder.ui");
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
		if(strcmp(lKey, "grid") == 0) {
			GGtk_Grid(app); lRunFlag = 1; break;
		}
		break;
	}
	if(lRunFlag == 0) GGtk_Default(app);
}
//===============================================
static void GGtk_OnQuit(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnRun(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnCreate(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnRead(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnUpdate(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
}
//===============================================
static void GGtk_OnDelete(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
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

	g_signal_connect(lButton, "clicked", G_CALLBACK(GGtk_OnQuit), NULL);
	g_signal_connect_swapped(lButton, "clicked", G_CALLBACK (gtk_widget_destroy), lWindow);

	gtk_widget_show_all(lWindow);
}
//===============================================
static void GGtk_Grid(GApplication *app) {
	GDebug()->Write(__FUNCTION__, 0);
	GtkWidget* lWindow = gtk_application_window_new(G_APPLICATION(app));
	gtk_window_set_title (GTK_WINDOW(lWindow), "Gtk | ReadyDev");
	gtk_window_set_default_size (GTK_WINDOW(lWindow), 640, 480);
	gtk_container_set_border_width (GTK_CONTAINER (lWindow), 10);

	GtkWidget* lGrid = gtk_grid_new();
	GtkWidget* lRun = gtk_button_new_with_label("Run");
	GtkWidget* lCreate = gtk_button_new_with_label("Create");
	GtkWidget* lRead = gtk_button_new_with_label("Read");
	GtkWidget* lUpdate = gtk_button_new_with_label("Update");
	GtkWidget* lDelete = gtk_button_new_with_label("Delete");

	gtk_grid_attach(GTK_GRID(lGrid), lCreate, 0, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(lGrid), lRead, 2, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(lGrid), lUpdate, 4, 0, 2, 1);
	gtk_grid_attach(GTK_GRID(lGrid), lDelete, 1, 1, 4, 1);
	gtk_grid_attach(GTK_GRID(lGrid), lRun, 0, 2, 6, 1);

	gtk_grid_set_row_homogeneous(GTK_GRID(lGrid), 0);
	gtk_grid_set_column_homogeneous(GTK_GRID(lGrid), 1);
	gtk_grid_set_row_spacing(GTK_GRID(lGrid), 10);
	gtk_grid_set_column_spacing(GTK_GRID(lGrid), 10);

	gtk_container_add(GTK_CONTAINER(lWindow), lGrid);

	g_signal_connect(lCreate, "clicked", G_CALLBACK(GGtk_OnCreate), NULL);
	g_signal_connect(lRead, "clicked", G_CALLBACK(GGtk_OnRead), NULL);
	g_signal_connect(lUpdate, "clicked", G_CALLBACK(GGtk_OnUpdate), NULL);
	g_signal_connect(lDelete, "clicked", G_CALLBACK(GGtk_OnDelete), NULL);
	g_signal_connect(lRun, "clicked", G_CALLBACK(GGtk_OnRun), NULL);

	gtk_widget_show_all(lWindow);
}
//===============================================
#endif
//===============================================
