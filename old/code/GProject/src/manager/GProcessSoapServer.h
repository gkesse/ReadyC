//===============================================
#ifndef _GProcessSoapServer_
#define _GProcessSoapServer_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSoapServerO GProcessSoapServerO;
//===============================================
struct _GProcessSoapServerO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSoapServer_New();
void GProcessSoapServer_Delete();
GProcessO* GProcessSoapServer();
//===============================================
#endif
//===============================================
