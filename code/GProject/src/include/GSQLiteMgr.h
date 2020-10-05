//===============================================
#ifndef _GSQLiteMgr_
#define _GSQLiteMgr_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GSQLiteMgrO GSQLiteMgrO;
//===============================================
struct _GSQLiteMgrO {
    void (*Delete)(); 
    void (*Test)(int argc, char** argv);
    void (*QueryShow)(char* sqlQuery, char* width, int widthD);
    void (*QueryWrite)(char* sqlQuery);
    void (*QueryValue)(char* sqlQuery, char* value);
    void (*QueryCol)(char* sqlQuery, char* row, char* sep);
    void (*QueryRow)(char* sqlQuery, char* row, char* sep);
};
//===============================================
GSQLiteMgrO* GSQLiteMgr_New();
void GSQLiteMgr_Delete();
GSQLiteMgrO* GSQLiteMgr();
//===============================================
#endif
//===============================================
