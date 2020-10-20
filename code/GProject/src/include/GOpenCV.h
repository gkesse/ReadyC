//===============================================
#ifndef _GOpenCV_
#define _GOpenCV_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GOpenCVO GOpenCVO;
//===============================================
struct _GOpenCVO {
    void (*Delete)(); 
    void (*Test)(int argc, char** argv);
    void (*Open)();
    void (*Close)();
};
//===============================================
GOpenCVO* GOpenCV_New();
void GOpenCV_Delete();
GOpenCVO* GOpenCV();
//===============================================
#endif
//===============================================
