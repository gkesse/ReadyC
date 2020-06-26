//===============================================
#ifndef _GProcessSoapClient_
#define _GProcessSoapClient_
//===============================================
#include "GProcess.h"
//===============================================
#if defined(_GUSE_GSOAP_ON_)
//===============================================
typedef struct _GProcessSoapClientO GProcessSoapClientO;
//===============================================
struct _GProcessSoapClientO {
    GProcessO* m_parent;
};
//===============================================
GProcessO* GProcessSoapClient_New();
void GProcessSoapClient_Delete();
GProcessO* GProcessSoapClient();
//===============================================
#endif
//===============================================
#endif
//===============================================
