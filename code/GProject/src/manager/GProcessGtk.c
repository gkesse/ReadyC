//===============================================
#include "GProcessGtk.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
#if defined(_GUSE_GTK_ON_)
//===============================================
static GProcessO* m_GProcessGtkO = 0;
//===============================================
static void GProcessGtk_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessGtk_New() {
    GProcessO* lParent = GProcess_New();
    GProcessGtkO* lChild = (GProcessGtkO*)malloc(sizeof(GProcessGtkO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessGtk_Delete;
    lParent->Run = GProcessGtk_Run;
    return lParent;
}
//===============================================
void GProcessGtk_Delete() {
	GProcess_Delete(m_GProcessGtkO);
	m_GProcessGtkO = 0;
}
//===============================================
GProcessO* GProcessGtk() {
    if(m_GProcessGtkO == 0) {
        m_GProcessGtkO = GProcessGtk_New();
    }
    return m_GProcessGtkO;
}
#if defined(__unix)
static void destroy (GtkWidget*, gpointer);
#endif
//===============================================
static void GProcessGtk_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessGtk_Run");
    //GLog()->Write("#================================================");
	GtkWidget *window, *button;

	  gtk_init (&argc, &argv);

	  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	  gtk_window_set_title (GTK_WINDOW (window), "Buttons");
	  gtk_container_set_border_width (GTK_CONTAINER (window), 25);
	  gtk_widget_set_size_request (window, 200, 100);

	  g_signal_connect (G_OBJECT (window), "destroy",
	                    G_CALLBACK (destroy), NULL);

	  /* Create a new button that has a mnemonic key of Alt+C. */
	  button = gtk_button_new_with_mnemonic ("_Close");
	  gtk_button_set_relief (GTK_BUTTON (button), GTK_RELIEF_NONE);

	  /* Connect the button to the clicked signal. The callback function recieves the
	   * window followed by the button because the arguments are swapped. */
	  g_signal_connect_swapped (G_OBJECT (button), "clicked",
	                            G_CALLBACK (gtk_widget_destroy),
	                            (gpointer) window);

	  gtk_container_add (GTK_CONTAINER (window), button);
	  gtk_widget_show_all (window);

	  gtk_main ();
}
//===============================================
#if defined(__unix)
static void
destroy (GtkWidget *window,
         gpointer data)
{
  gtk_main_quit ();
}
#endif
//===============================================
#endif
//===============================================
