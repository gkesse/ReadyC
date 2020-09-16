//===============================================
#ifndef _GDate_
#define _GDate_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GDateO GDateO;
//===============================================
struct _GDateO {
    void (*Delete)(); 
    void (*Test)(int argc, char** argv);
    void (*Date)(char* buffer);
    void (*Time)(char* buffer);
    void (*DateTime)(char* buffer);
};
//===============================================
GDateO* GDate_New();
void GDate_Delete();
GDateO* GDate();
//===============================================
#endif
//===============================================
