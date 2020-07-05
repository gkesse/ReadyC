//===============================================
#ifndef _GShell_
#define _GShell_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GShellO GShellO;
//===============================================
struct _GShellO {
	void (*Delete)();
    void (*Run)(const char* command, char* output, int size, int shift);
};
//===============================================
GShellO* GShell_New();
void GShell_Delete();
GShellO* GShell();
//===============================================
#endif
//===============================================
