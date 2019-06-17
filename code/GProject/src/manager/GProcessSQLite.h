//===============================================
#ifndef _GProcessSQLite_
#define _GProcessSQLite_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSQLiteO GProcessSQLiteO;
//===============================================
struct _GProcessSQLiteO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSQLite_New();
void GProcessSQLite_Delete(GProcessO* obj);
GProcessO* GProcessSQLite();
//===============================================
#endif
//===============================================
