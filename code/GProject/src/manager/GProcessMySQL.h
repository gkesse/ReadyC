//===============================================
#ifndef _GProcessMySQL_
#define _GProcessMySQL_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessMySQLO GProcessMySQLO;
//===============================================
struct _GProcessMySQLO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessMySQL_New();
void GProcessMySQL_Delete();
GProcessO* GProcessMySQL();
//===============================================
#endif
//===============================================
