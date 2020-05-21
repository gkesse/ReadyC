//===============================================
#include "GShell.h"
#include "GDebug.h"
//===============================================
static GShellO* m_GShellO = 0;
//===============================================
static void GShell_Test(int argc, char** argv);
static void GShell_Run(char* command, char* output, int size, int shift);
//===============================================
#if defined(__unix)
static void GShell_TestUnix(int argc, char** argv);
#elif defined(__WIN32)
static void GShell_TestWin(int argc, char** argv);
#endif
//===============================================
GShellO* GShell_New() {
    GShellO* lObj = (GShellO*)malloc(sizeof(GShellO));

    lObj->Delete = GShell_Delete;
    lObj->Test = GShell_Test;
    lObj->Run = GShell_Run;
    return lObj;
}
//===============================================
void GShell_Delete() {

}
//===============================================
GShellO* GShell() {
    if(m_GShellO == 0) {
        m_GShellO = GShell_New();
    }
    return m_GShellO;
}
//===============================================
static void GShell_Test(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
#if defined(__unix)
    GShell_TestUnix(argc, argv);
#elif defined(__WIN32)
    GShell_TestWin(argc, argv);
#endif
}
//===============================================
#if defined(__unix)
static void GShell_TestUnix(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    char lCommand[256];
    char lOuput[256];

    sprintf(lCommand, "%s", "echo $HOME");
    GShell()->Run(lCommand, lOuput, 255, 1);
    printf("%s: %s\n", "HOME", lOuput);
}
#endif
//===============================================
#if defined(__WIN32)
static void GShell_TestWin(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
}
#endif
//===============================================
static void GShell_Run(char* command, char* output, int size, int shift) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    FILE* lpFile = popen(command, "r");
    if(output != 0) {
        int lBytes = fread(output, 1, size, lpFile);
        if(lBytes >= 1) {
            output[lBytes] = 0;
            if(shift == 1) output[lBytes - 1] = 0;
        }
    }
    pclose(lpFile);
}
//===============================================
