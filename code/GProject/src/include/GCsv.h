//===============================================
#ifndef _GCsv_
#define _GCsv_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GCsvO GCsvO;
typedef struct _GListO_GCsv_GVOID_PTR GListO_GCsv_GVOID_PTR;
//===============================================
struct _GCsvO {
    void (*Delete)();
    void (*Clear)();
    void (*Remove)(int key);
    void (*AddRow)();
    void (*AddData)(char* value);
    void (*SetData)(int row, int col, char* data);
    char* (*GetData)(int row, int col);
    void (*Size)(int* width, int* height);
    void (*Show)();
    GListO_GCsv_GVOID_PTR* m_dataMap;
    GListO_GCsv_GVOID_PTR* m_listMap;
};
//===============================================
GCsvO* GCsv_New();
void GCsv_Delete();
GCsvO* GCsv();
//===============================================
#endif
//===============================================