//===============================================
#ifndef _GProcessTest_
#define _GProcessTest_
//===============================================
#include "GProcess.h"
#include "GList.h"
//===============================================
typedef struct _GProcessTestO GProcessTestO;
typedef struct _GListO_GProcessTest_GINT_PTR GListO_GProcessTest_GINT_PTR;
typedef struct _GListO_GProcessTest_GCHAR_PTR GListO_GProcessTest_GCHAR_PTR;
//===============================================
struct _GProcessTestO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessTest_New();
void GProcessTest_Delete();
GProcessO* GProcessTest();
//===============================================
#endif
//===============================================
