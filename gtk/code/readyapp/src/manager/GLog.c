//===============================================
#include "GLog.h"
#include "GList.h"
#include "GManager.h"
//===============================================
GDECLARE_LIST(GLog, GVOID_PTR)
GDEFINE_LIST(GLog, GVOID_PTR)
//===============================================
#define B_LOG (1024)
//===============================================
static GLogO* m_GLogO = 0;
//===============================================
typedef int (*GLOG_FUNC)(char* buffer, int index, void* obj);
//===============================================
typedef struct _sGPerson sGPerson;
//===============================================
static void GLog_Test(int argc, char** argv);
static void GLog_Write(int key, ...);
static void GLog_Sep();
static void GLog_Buffer(char* buffer);
static FILE* GLog_Open();
static void GLog_Close(FILE* file);
static char* GLog_Date();
static int GLog_OnTest(char* buffer, int index, void* obj);
//===============================================
struct _sGPerson {
    char* firstname;
    char* lastname;
    char* email;
    int code;
};
//===============================================
GLogO* GLog_New() {
    GLogO* lObj = (GLogO*)malloc(sizeof(GLogO));
    lObj->Delete = GLog_Delete;
    lObj->Test = GLog_Test;
    lObj->Sep = GLog_Sep;
    lObj->Write = GLog_Write;
    return lObj;
}
//===============================================
void GLog_Delete() {

}
//===============================================
GLogO* GLog() {
    if(m_GLogO == 0) {
        m_GLogO = GLog_New();
    }
    return m_GLogO;
}
//===============================================
// method
//===============================================
static void GLog_Test(int argc, char** argv) {
    sGPerson lPerson = {"Gerard", "KESSE", "gerard.kesse@outlook.fr", 1234};
    
    GLog()->Sep();
    GLog()->Write(30, -25, "afficher un entier ", 3, " : ", 1, 10000, 0);
    GLog()->Write(30, -25, "afficher un reel ", 3, " : ", 2, 3.14, 0);
    GLog()->Write(30, -25, "afficher un chaine ", 3, " : ", 3, "Bonjour tout le monde", 0);
    GLog()->Write(30, -25, "afficher une structure ", 3, " : ", 3, "\n", 4, GLog_OnTest, &lPerson, 0);
    GLog()->Sep();
}
//===============================================
static int GLog_OnTest(char* buffer, int index, void* obj) {
    sGPerson* lPerson = obj;
    index += sprintf(&buffer[index], "%*s%*s : %s\n", 5, "", -10, "Nom", lPerson->lastname);
    index += sprintf(&buffer[index], "%*s%*s : %s\n", 5, "", -10, "Prenom", lPerson->firstname);
    index += sprintf(&buffer[index], "%*s%*s : %s\n", 5, "", -10, "Email", lPerson->email);
    index += sprintf(&buffer[index], "%*s%*s : %d\n", 5, "", -10, "Code", lPerson->code);
    return index;
}
//===============================================
static void GLog_Write(int key, ...) {
    sGApp* lApp = GManager()->mgr->app;
    if(lApp->log_on == 0) return;
    char lBuffer[B_LOG+1];
    int lIndex = 0;

    va_list lArgs;
    va_start(lArgs, key);
    int lType = key;
    while(1) {
        // off
        if(lType == 0) break;
        // int
        if(lType == 1) {
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%d", lData);
        }
        // int - width
        else if(lType == 10) {
            int lWidth = va_arg(lArgs, int);
            int lData = va_arg(lArgs, int);
            lIndex += sprintf(&lBuffer[lIndex], "%*d", lWidth, lData);
        }
        // double 
        else if(lType == 2) {
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%f", lData);
        }
        // double - width
        else if(lType == 20) {
            int lWidth = va_arg(lArgs, int);
            double lData = va_arg(lArgs, double);
            lIndex += sprintf(&lBuffer[lIndex], "%.*f", lWidth, lData);
        }
        // string
        else if(lType == 3) {
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%s", lData);
        }
        // string - width
        else if(lType == 30) {
            int lWidth = va_arg(lArgs, int);
            char* lData = va_arg(lArgs, char*);
            lIndex += sprintf(&lBuffer[lIndex], "%*s", lWidth, lData);
        }
        // struct
        else if(lType == 4) {
            GLOG_FUNC onLogFunc = (GLOG_FUNC)va_arg(lArgs, void*);
            void* lObj = va_arg(lArgs, void*);
            lIndex += onLogFunc(lBuffer, lIndex, lObj);
        }
        lType = va_arg(lArgs, int);
    }
    va_end(lArgs);
    GLog_Buffer(lBuffer);
}
//===============================================
static void GLog_Sep() {
    char lBuffer[256];
    for(int i = 0; i < 50; i++) {
        sprintf(&lBuffer[i], "=");
    }
    GLog_Buffer(lBuffer);
}
//===============================================
static void GLog_Buffer(char* buffer) {
    FILE* lFile = GLog_Open();
    char* lDate = GLog_Date();
    char lFormat[256];
    
    GListO(GLog, GVOID_PTR)* lLines = GManager()->Split(buffer, "\n");
    
    for(int i = 0; i < lLines->Size(lLines); i++) {
        char* lLine = lLines->GetData(lLines, i);
        sprintf(lFormat, "%s | %s", lDate, lLine);
        fprintf(lFile, "%s\n", lFormat);
    }
    
    GLog_Close(lFile);
    free(lDate);
    lLines->Delete(lLines, 0);
}
//===============================================
static FILE* GLog_Open() {
    sGApp* lApp = GManager()->mgr->app;
    FILE* lFile = 0;
    if(!strcmp(lApp->log_mode, "file")) {
        lFile = fopen(lApp->log_path , "a+");
    }
    else if(!strcmp(lApp->log_mode, "stdout")) {
        lFile = stdout;
    }
    else if(!strcmp(lApp->log_mode, "stderr")) {
        lFile = stderr;
    }
    else {
        lFile = stdout;
    }
    return lFile;
}
//===============================================
static void GLog_Close(FILE* file) {
    sGApp* lApp = GManager()->mgr->app;
    if(!strcmp(lApp->log_mode, "file")) {
        fclose(file);
    }
}
//===============================================
static char* GLog_Date() {
    char lBuffer[B_LOG+1];
    time_t lTime;
    time(&lTime);
    struct tm* lTimeInfo = localtime(&lTime);
    int lDay = lTimeInfo->tm_mday;
    int lMonth = lTimeInfo->tm_mon + 1;
    int lYear = lTimeInfo->tm_year + 1900;
    int lHour = lTimeInfo->tm_hour;
    int lMin = lTimeInfo->tm_min;
    int lSec = lTimeInfo->tm_sec;
    sprintf(lBuffer, "%02d/%02d/%04d %02d:%02d:%02d", lDay, lMonth, lYear, lHour, lMin, lSec);
    return GManager()->CopyStr(lBuffer);
}
//===============================================
