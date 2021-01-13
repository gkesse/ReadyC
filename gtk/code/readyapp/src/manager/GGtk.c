//===============================================
#include "GGtk.h"
#include "GWidget.h"
#include "GManager.h"
//===============================================
static GGtkO* m_GGtkO = 0;
//===============================================
static void GGtk_Run(int argc, char** argv);
//===============================================
GGtkO* GGtk_New() {
    GGtkO* lObj =(GGtkO*)malloc(sizeof(GGtkO));
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
    gtk_init(&argc, &argv);

    GManager()->LoadStyle();
    GWidget("window");

    gtk_main();
}
//===============================================
