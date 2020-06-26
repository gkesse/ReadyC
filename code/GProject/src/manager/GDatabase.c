//===============================================
#include "GDatabase.h"
#include "GSQLite.h"
//#include "GMySQL.h"
#include "GString2.h"
#include "GConfig.h"
//===============================================
GDatabaseO* GDatabase_New() {
    GDatabaseO* lObj = (GDatabaseO*)malloc(sizeof(GDatabaseO));
    lObj->m_child = 0;
    return lObj;
}
//===============================================
void GDatabase_Delete(GDatabaseO* obj) {
    if(obj != 0) {
        if(obj->m_child != 0) {
            free(obj->m_child);
        }
        free(obj);
    }
}
//===============================================
GDatabaseO* GDatabase() {
    char* lKey = GConfig()->GetData("DATABASE");
    if(GString2()->IsEqual(lKey, "SQLITE")) return GSQLite();
    //if(GString2()->IsEqual(lKey, "MYSQL")) return GMySQL();
    return GSQLite();
}
//===============================================
