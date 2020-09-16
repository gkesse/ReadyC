//===============================================
#ifndef _GConfig_
#define _GConfig_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GConfigO GConfigO;
typedef struct _GMapO_GConfig_GCHAR_PTR_GVOID_PTR GMapO_GConfig_GCHAR_PTR_GVOID_PTR;
//===============================================
struct _GConfigO {
    void (*Delete)();
    void (*Clear)();
    void (*Remove)(char* key);
    void (*SetData)(char* key, char* value);
    char* (*GetData)(char* key);
    void (*SaveData)(char* key);
    void (*LoadData)(char* key);
    int (*Size)();
    void (*Show)();
    GMapO_GConfig_GCHAR_PTR_GVOID_PTR* m_dataMap;
};
//===============================================
GConfigO* GConfig_New();
void GConfig_Delete();
GConfigO* GConfig();
//===============================================
#endif
//===============================================