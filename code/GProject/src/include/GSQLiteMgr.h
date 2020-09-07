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
    void (*QueryShow)(char* sqlQuery);
};
//===============================================
GSQLiteMgrO* GSQLiteMgr_New();
void GSQLiteMgr_Delete();
GSQLiteMgrO* GSQLiteMgr();
//===============================================
#endif
//===============================================
