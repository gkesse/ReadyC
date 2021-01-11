//===============================================
#include "GGtk.h"
#include "GWidget.h"
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Run(int argc, char** argv);
//===============================================
GGtkO* GGtk_New() {
    GGtkO* lObj = (GGtkO*)malloc(sizeof(GGtkO));
    lObj->Delete = GGtk_Delete;
    lObj->Run = GGtk_Run;
    return lObj;
}
//===============================================
void GGtk_Delete() {

}
//===============================================
GGtkO* GGtk() {
    if(m_GGtkO == 0) {
        m_GGtkO = GGtk_New();
    }
    return m_GGtkO;
}
//===============================================
static void GGtk_Run(int argc, char** argv) {
    gtk_init (&argc, &argv);

    GWidget* lWindow = GWidget_Create("windowgtk");
    gtk_widget_show_all(GTK_WIDGET(lWindow));

    gtk_main ();
}
//===============================================
