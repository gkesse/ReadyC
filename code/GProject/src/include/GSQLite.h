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
    void (*Test)(int argc, char** argv);
    void (*QueryShow)(char* sqlQuery, char* width, int widthD);
    void (*QueryWrite)(char* sqlQuery);
    void (*QueryValue)(char* sqlQuery, char* value);
    void (*QueryCol)(char* sqlQuery, char* row, char* sep);
    void (*QueryRow)(char* sqlQuery, char* row, char* sep);
};
//===============================================
GSQLiteO* GSQLite_New();
void GSQLite_Delete();
GSQLiteO* GSQLite();
//===============================================
#endif
//===============================================
