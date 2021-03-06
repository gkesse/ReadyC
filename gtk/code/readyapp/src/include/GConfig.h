//===============================================
#ifndef _GConfig_
#define _GConfig_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GConfigO GConfigO;
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
    void* dataMap;
};
//===============================================
GConfigO* GConfig_New();
void GConfig_Delete();
GConfigO* GConfig();
//===============================================
#endif
//===============================================