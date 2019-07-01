//===============================================
#ifndef _GProcessSoap_
#define _GProcessSoap_
//===============================================
#include "GProcess.h"
//===============================================
typedef struct _GProcessSoapO GProcessSoapO;
//===============================================
struct _GProcessSoapO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSoap_New();
void GProcessSoap_Delete();
GProcessO* GProcessSoap();
//===============================================
#endif
//===============================================
