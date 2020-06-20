<<<<<<< HEAD
//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessO GProcessO;
//===============================================
struct _GProcessO {
    void (*Delete)();
    void (*Run)(int argc, char** argv);
};
//===============================================
GProcessO* GProcess_New();
void GProcess_Delete();
GProcessO* GProcess();
//===============================================
#endif
//===============================================
=======
//===============================================
#ifndef _GProcess_
#define _GProcess_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GProcessO GProcessO;
//===============================================
struct _GProcessO {
	void (*Delete)();
	void (*Run)(int argc, char** argv);
	void (*Test)(int argc, char** argv);
};
//===============================================
GProcessO* GProcess_New();
void GProcess_Delete();
GProcessO* GProcess();
//===============================================
#endif
//===============================================
>>>>>>> bd9c6b9e67282519751bdf6eeca1c21834218466
