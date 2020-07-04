//===============================================
#include "GString3.h"
#include "GDebug.h"
//===============================================
static GString3O* m_GString3O = 0;
//===============================================
static char* GString3_Copy(char* str);
static char* GString3_Trim(char* str);
static char** GString3_Split(char* str, char* sep, int* count);
static void GString3_ToUpper(char* str, char* output);
static void GString3_ToLower(char* str, char* output);
static void GString3_Free(char* ptr);
static void GString3_Free2(char** ptr, int size);
//===============================================
GString3O* GString3_New() {
    GString3O* lObj = (GString3O*)malloc(sizeof(GString3O));
    
    lObj->Delete = GString3_Delete;
    lObj->Trim = GString3_Trim;
    lObj->Copy = GString3_Copy;
    lObj->Split = GString3_Split;
    lObj->ToUpper = GString3_ToUpper;
    lObj->ToLower = GString3_ToLower;
    lObj->Free = GString3_Free;
    lObj->Free2 = GString3_Free2;
    return lObj; 
}
//===============================================
void GString3_Delete() {

}
//===============================================
GString3O* GString3() {
    if(m_GString3O == 0) {
        m_GString3O = GString3_New();
    }
    return m_GString3O;
}
//===============================================
static char* GString3_Trim(char* str) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
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
static char* GString3_Copy(char* str) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lLength = strlen(str);
    char* lCopy = (char*)malloc(sizeof(char)*(lLength + 1));
    strcpy(lCopy, str);
    return lCopy;
}
//===============================================
static char** GString3_Split(char* str, char* sep, int* count) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
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
    char* lStr = GString3()->Copy(str);
    char* lToken = strtok(lStr, sep);
    int lTok = 0;
    while(lToken != 0) {
        lSplit[lTok] = GString3()->Copy(lToken);
        lToken = strtok(0, sep);
        lTok++;
    }
    free(lStr);
    return lSplit;
}
//===============================================
static void GString3_ToUpper(char* str, char* output) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lSize = strlen(str);
    for(int i = 0; i < lSize; i ++) {
        output[i] = toupper(str[i]);
    }
    output[lSize] = 0;
}
//===============================================
static void GString3_ToLower(char* str, char* output) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lSize = strlen(str);
    for(int i = 0; i < lSize; i ++) {
        output[i] = tolower(str[i]);
    }
    output[lSize] = 0;
}
//===============================================
static void GString3_Free(char* ptr) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    free(ptr);
}
//===============================================
static void GString3_Free2(char** ptr, int size) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    for(int i = 0; i < size; i++) {
        free(ptr[i]);
    }
    free(ptr);
}
//===============================================