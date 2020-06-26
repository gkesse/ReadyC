//===============================================
#ifndef _GMainLoop2_
#define _GMainLoop2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GMainLoop2O GMainLoop2O;
//===============================================
struct _GMainLoop2O {
    void (*Delete)();
    void (*Exec)();
    void (*Run)();
};
//===============================================
GMainLoop2O* GMainLoop2_New();
void GMainLoop2_Delete();
GMainLoop2O* GMainLoop2();
//===============================================
#endif
//===============================================
