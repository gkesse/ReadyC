//===============================================
#include "GString3.h"
#include "GDebug.h"
//===============================================
static GString3O* m_GString3O = 0;
//===============================================
static void GString3_ToUpper(const char* strIn, char* strOut);
static void GString3_ToLower(const char* strIn, char* strOut);
static void GString3_Trim(const char* strIn, char* strOut);
static void GString3_SplitGet(const char* strIn, char* strOut, char* sep, int index);
static int GString3_SplitCount(const char* strIn, char* sep);
static void GString3_Replace(const char* strIn, char* strOut, const char* pattern, const char* replace);
//===============================================
GString3O* GString3_New() {
    GString3O* lObj = (GString3O*)malloc(sizeof(GString3O));
    
    lObj->ToUpper = GString3_ToUpper;
    lObj->ToLower = GString3_ToLower;
    lObj->Delete = GString3_Delete;
    lObj->Trim = GString3_Trim;
    lObj->SplitGet = GString3_SplitGet;
    lObj->SplitCount = GString3_SplitCount;
    lObj->Replace = GString3_Replace;
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
static void GString3_ToUpper(const char* strIn, char* strOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lSize = strlen(strIn);
    for(int i = 0; i < lSize; i ++) {
        strOut[i] = toupper(strIn[i]);
    }
    strOut[lSize] = 0;
}
//===============================================
static void GString3_ToLower(const char* strIn, char* strOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lSize = strlen(strIn);
    for(int i = 0; i < lSize; i ++) {
        strOut[i] = tolower(strIn[i]);
    }
    strOut[lSize] = 0;
}
//===============================================
static void GString3_Trim(const char* strIn, char* strOut) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lPos = 0;
    int lLeft = 0;
    int lFlag = 0;
    while(strIn[lPos] != 0) {
        if(lFlag == 0) {
            char lChar = strIn[lPos];
            if(isspace(lChar) == 0) lFlag = 1;
            else lPos++;
        }
        if(lFlag == 1) {
            lLeft = lPos;
            break;
        }
    }
    lPos = strlen(strIn) - 1;
    int lRight = 0;
    lFlag = 0;
    while(lPos >= 0) {
        if(lFlag == 0) {
            char lChar = strIn[lPos];
            if(isspace(lChar) == 0) lFlag = 1;
            else lPos--;
        }
        if(lFlag == 1) {
            lRight = lPos;
            break;
        }
    }
    int lOut = 0;
    for(lPos = lLeft; lPos <= lRight; lPos++, lOut++) {
        strOut[lOut] = strIn[lPos];
    }
    strOut[lOut] = 0;
}
//===============================================
static void GString3_SplitGet(const char* strIn, char* strOut, char* sep, int index) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lPos = 0;
    int lOut = 0;
    int lCount = 0;
    int lFlag = 0;
    while(strIn[lPos] != 0) {
        if(lFlag == 0) {
            if(lCount == index) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            char lChar = strIn[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) break;
            strOut[lOut] = lChar;
            lPos++; lOut++;
        }
        if(lFlag == 2) {
            char lChar = strIn[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) lCount++;
            lPos++;
            lFlag = 0;
        }
    }
    strOut[lOut] = 0;
}
//===============================================
static int GString3_SplitCount(const char* strIn, char* sep) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lPos = 0;
    int lCount = 0;
    while(strIn[lPos] != 0) {
        char lChar = strIn[lPos];
        char* lSearch = strchr(sep, lChar);
        if(lSearch != 0) lCount++;
        lPos++;
    }
    lCount += 1;
    return lCount;
}
//===============================================
static void GString3_Replace(const char* strIn, char* strOut, const char* pattern, const char* replace) {
    GDebug()->Write(1, __FUNCTION__, "()", _EOA_);
    int lFlag = 0;
    int lOut = 0;
    
    strcpy(strIn, strOut);
    while(1) {
        if(lFlag == 0) {
            char* lPattern = strstr(strIn, pattern);
            if(lPattern == 0) break;
        }
    }
}
//===============================================
