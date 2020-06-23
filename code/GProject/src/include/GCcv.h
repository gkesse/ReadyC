//===============================================
#ifndef _GCcv_
#define _GCcv_
//===============================================
#include "GInclude.h"
//===============================================
#if defined(_GUSE_CCV_ON_)
//===============================================
typedef struct _GCcvO GCcvO;
typedef struct _GMapO_GCcv_GCHAR_PTR_GVOID_PTR GMapO_GCcv_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GCcvO {
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    void (*CreateMatrix)(char* matrixId);
    //===============================================
    GMapO_GCcv_GCHAR_PTR_GVOID_PTR* m_matrixMap;
    GMapO_GCcv_GCHAR_PTR_GVOID_PTR* m_cascadeMap;
    GMapO_GCcv_GCHAR_PTR_GVOID_PTR* m_facesMap;
};
//===============================================
GCcvO* GCcv_New();
void GCcv_Delete();
GCcvO* GCcv();
//===============================================
#endif
//===============================================
#endif
//===============================================