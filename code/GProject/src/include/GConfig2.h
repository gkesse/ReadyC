//===============================================
#ifndef _GConfig2_
#define _GConfig2_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GConfig2O GConfig2O;
typedef struct _GMapO_GConfig2_GCHAR_PTR_GVOID_PTR GMapO_GConfig2_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GConfig2O {
    void (*Delete)();
    void (*Clear)();
    void (*Remove)(char* key);
    void (*SetData)(char* key, char* value);
    char* (*GetData)(char* key);
    int (*Size)();
    void (*Show)();
    GMapO_GConfig2_GCHAR_PTR_GVOID_PTR* m_dataMap;
};
//===============================================
GConfig2O* GConfig2_New();
void GConfig2_Delete();
GConfig2O* GConfig2();
//===============================================
#endif
//===============================================