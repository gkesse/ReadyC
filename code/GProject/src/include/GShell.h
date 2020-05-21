//===============================================
#ifndef _GShell_
#define _GShell_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GShellO GShellO;
//===============================================
#define _EOA_ "_END_OF_ARGUMENT_"
//===============================================
struct _GShellO {
	void (*Delete)();
	void (*Test)(int argc, char** argv);
    void (*Run)(char* command, char* output, int size, int shift);
};
//===============================================
GShellO* GShell_New();
void GShell_Delete();
GShellO* GShell();
//===============================================
#endif
//===============================================
