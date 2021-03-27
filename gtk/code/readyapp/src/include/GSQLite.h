//===============================================
#ifndef _GSQLite_
#define _GSQLite_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLiteO GSQLiteO;
//===============================================
struct _GSQLiteO {
    void (*Delete)(); 
    void (*ShowVersion)();
    void (*QueryShow)(char* sqlQuery, char* widthMap, int defaultWidth);
    void (*QueryWrite)(char* sqlQuery);
    void* (*QueryValue)(char* sqlQuery);
    void* (*QueryCol)(char* sqlQuery);
    void* (*QueryRow)(char* sqlQuery);
    void* (*QueryMap)(char* sqlQuery);
};
//===============================================
GSQLiteO* GSQLite_New();
void GSQLite_Delete();
GSQLiteO* GSQLite();
//===============================================
#endif
//===============================================
