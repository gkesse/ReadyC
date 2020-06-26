//===============================================
#ifndef _GProcessDatabase_
#define _GProcessDatabase_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessDatabaseO GProcessDatabaseO;
//===============================================
struct _GProcessDatabaseO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessDatabase_New();
void GProcessDatabase_Delete();
GProcessO* GProcessDatabase();
//===============================================
#endif
//===============================================
