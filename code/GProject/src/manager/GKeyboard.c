//===============================================
#include "GKeyboard.h"
//===============================================
static GKeyboardO* m_GKeyboardO = 0;
//===============================================
GKeyboardO* GKeyboard_New() {
    GKeyboardO* lObj = (GKeyboardO*)malloc(sizeof(GKeyboardO));
    lObj->Delete = GKeyboard_Delete;
    lObj->Input = scanf;
    lObj->Line = fgets;
    lObj->Clear = fflush;
    return lObj;
}
//===============================================
void GKeyboard_Delete() {
    GKeyboardO* lObj = GKeyboard();
    if(lObj != 0) {
        free(lObj);
    }
    m_GKeyboardO = 0;
}
//===============================================
GKeyboardO* GKeyboard() {
    if(m_GKeyboardO == 0) {
        m_GKeyboardO = GKeyboard_New();
    }
    return m_GKeyboardO;
}
//===============================================
