//===============================================
#ifndef _GLog_
#define _GLog_
//===============================================
#include "GInclude.h"
//===============================================
#define GLOG_BUFFER_FILENAME    256
#define GLOG_BUFFER_PREFIX      256
//===============================================
typedef struct _GLogO GLogO;
//===============================================
struct _GLogO {
    void (*Delete)();
    void (*Write)(char* data);
    char m_filename[GLOG_BUFFER_FILENAME];
    char m_prefix[GLOG_BUFFER_PREFIX];
};
//===============================================
GLogO* GLog_New();
void GLog_Delete();
GLogO* GLog();
//===============================================
#endif
//===============================================
