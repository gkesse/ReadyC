//===============================================
#ifndef _GOpenCV_
#define _GOpenCV_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GOpenCVO GOpenCVO;
//===============================================
struct _GOpenCVO {
    void* child;
    void (*Delete)(); 
    void (*Test)(int argc, char** argv);
    void (*Open)();
    void (*OnOpen)();
};
//===============================================
GOpenCVO* GOpenCV_New();
void GOpenCV_Delete();
GOpenCVO* GOpenCV();
//===============================================
#endif
//===============================================
