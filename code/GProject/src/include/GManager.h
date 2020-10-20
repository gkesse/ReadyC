//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
#define B_APP_NAME (64)
#define B_HOME_PATH (256)
#define B_DATA_PATH (256)
#define B_SQLITE_DB (256)
#define B_JSON_FILE (256)
#define B_WIN_TITLE (256)
//===============================================
typedef struct _GManagerO GManagerO;
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
typedef struct _sGSQLite sGSQLite;
typedef struct _sGJson sGJson;
typedef struct _sGOpenCV sGOpenCV;
//===============================================
struct _GManagerO {
    // global
    void* child;
    void (*Delete)();
    void (*Test)(int argc, char** argv);
    void (*Main)();
    void (*DataShow)();
    // terminal
    void (*Printf)(const char* format, ...);
    void (*ReadLine)(char* buffer, int size);
    // string
    char* (*Copy)(char* strIn);
    void (*ToUpper)(char* strIn, char* strOut);
    void (*ToLower)(char* strIn, char* strOut);
    void (*Trim)(char* strIn, char* strOut);
    int (*SplitCount)(char* strIn, char* sep);
    void (*SplitGet)(char* strIn, char* strOut, char* sep, int index);
    void (*Replace)(char* strIn, char* strOut, char* pattern, char* replace);
    // date
    void (*Date)(char* buffer);
    // trace
    void (*Trace)(int key, ...);
    // data
    sGManager* m_mgr;
};
//===============================================
GManagerO* GManager_New();
void GManager_Delete();
GManagerO* GManager();
//===============================================
struct _sGManager {
    sGApp* app;
    sGSQLite* sqlite;
    sGJson* json;
    sGOpenCV* opencv;
};
//===============================================
struct _sGApp {
    char app_name[B_APP_NAME+1];
    char home_path[B_HOME_PATH+1];
    char data_path[B_DATA_PATH+1];
    char trace_file[B_DATA_PATH+1];
    int trace_on;
    char* trace_mode;
    int date_on;
};
//===============================================
struct _sGSQLite {
    char db_path[B_SQLITE_DB+1];
};
//===============================================
struct _sGJson {
    char file[B_JSON_FILE+1];
};
//===============================================
struct _sGOpenCV {
    char win_title[B_WIN_TITLE+1];
    int win_width;
    int win_height;
    IplImage* win_img;
    IplImage* bg_img;
    CvScalar bg_color;
    int delay;
    int run_me;
#if defined(__unix)
    pthread_t thread_id;
#elif defined(__WIN32)
    DWORD thread_id;
#endif
};
//===============================================
#endif
//===============================================