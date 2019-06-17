//===============================================
#ifndef _GConfigNormal_
#define _GConfigNormal_
//===============================================
#include "GConfig.h"
//===============================================
typedef struct _GConfigNormalO GConfigNormalO;
typedef struct _GConfigNodeO GConfigNodeO;
//===============================================
struct _GConfigNodeO {
    int m_index;
    char* m_key;
    char* m_value;
    GConfigNodeO* m_next;
};
//===============================================
struct _GConfigNormalO {
    GConfigO* m_parent;
    GConfigNodeO* m_head;
};
//===============================================
GConfigO* GConfigNormal_New();
void GConfigNormal_Delete();
GConfigO* GConfigNormal();
//===============================================
#endif
//===============================================
