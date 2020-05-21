//===============================================
#include "GString.h"
#include "GDebug.h"
//===============================================
static GStringO* m_GStringO = 0;
//===============================================
static void GString_Test(int argc, char** argv);
static char* GString_Copy(char* str);
static char* GString_Trim(char* str);
static char** GString_Split(char* str, char* sep, int* count);
static void GString_ToUpper(char* str, char* output);
static void GString_ToLower(char* str, char* output);
static void GString_Free(char* ptr);
static void GString_Free2(char** ptr, int size);
//===============================================
GStringO* GString_New() {
    GStringO* lObj = (GStringO*)malloc(sizeof(GStringO));
    
    lObj->Delete = GString_Delete;
    lObj->Test = GString_Test;
    lObj->Trim = GString_Trim;
    lObj->Copy = GString_Copy;
    lObj->Split = GString_Split;
    lObj->ToUpper = GString_ToUpper;
    lObj->ToLower = GString_ToLower;
    lObj->Free = GString_Free;
    lObj->Free2 = GString_Free2;
    return lObj; 
}
//===============================================
void GString_Delete() {

}
//===============================================
GStringO* GString() {
    if(m_GStringO == 0) {
        m_GStringO = GString_New();
    }
    return m_GStringO;
}
//===============================================
static void GString_Test(int argc, char** argv) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
}
//===============================================
static char* GString_Trim(char* str) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    if(str[0] == 0) return 0;
    int lStart = 0;
    int lEnd = strlen(str) - 1;
    while(isspace(str[lStart]) != 0 && lStart < lEnd) lStart++;
    while(isspace(str[lEnd]) != 0 && lEnd > lStart) lEnd--;
    if(lStart == lEnd) {if(isspace(str[lStart]) != 0) {return 0;}}
    lEnd += 1;
    int lLength = lEnd - lStart;
    char* lTrim = (char*)malloc(sizeof(char)*(lLength + 1));
    int i = lStart;
    int j = 0;
    while(i < lEnd) {
        lTrim[j] = str[i];
        i++;
        j++;
    }
    lTrim[j] = 0;
    return lTrim;
}
//===============================================
static char* GString_Copy(char* str) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    int lLength = strlen(str);
    char* lCopy = (char*)malloc(sizeof(char)*(lLength + 1));
    strcpy(lCopy, str);
    return lCopy;
}
//===============================================
static char** GString_Split(char* str, char* sep, int* count) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    int lPos = 0;
    int lCount = 0;
    while(str[lPos] != 0) {
        char lChar = str[lPos];
        char* lSearch = strchr(sep, lChar);
        if(lSearch != 0) lCount++;
        lPos++;
    }
    lCount += 1;
    *count = lCount;
    char** lSplit = (char**)malloc(sizeof(char*)*lCount);
    char* lStr = GString()->Copy(str);
    char* lToken = strtok(lStr, sep);
    int lTok = 0;
    while(lToken != 0) {
        lSplit[lTok] = GString()->Copy(lToken);
        lToken = strtok(0, sep);
        lTok++;
    }
    free(lStr);
    return lSplit;
}
//===============================================
static void GString_ToUpper(char* str, char* output) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    int lSize = strlen(str);
    for(int i = 0; i < lSize; i ++) {
        output[i] = toupper(str[i]);
    }
    output[lSize] = 0;
}
//===============================================
static void GString_ToLower(char* str, char* output) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    int lSize = strlen(str);
    for(int i = 0; i < lSize; i ++) {
        output[i] = tolower(str[i]);
    }
    output[lSize] = 0;
}
//===============================================
static void GString_Free(char* ptr) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    free(ptr);
}
//===============================================
static void GString_Free2(char** ptr, int size) {
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    for(int i = 0; i < size; i++) {
        free(ptr[i]);
    }
    free(ptr);
}
//===============================================