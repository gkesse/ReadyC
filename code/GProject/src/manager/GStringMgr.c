//===============================================
#include "GStringMgr.h"
//===============================================
#define B_STRING_SIZE (1024)
//===============================================
static GStringMgrO* m_GStringMgrO = 0;
//===============================================
static char* GStringMgr_Copy(const char* strIn);
static void GStringMgr_ToUpper(const char* strIn, char* strOut);
static void GStringMgr_ToLower(const char* strIn, char* strOut);
static void GStringMgr_Trim(const char* strIn, char* strOut);
static void GStringMgr_SplitGet(const char* strIn, char* strOut, char* sep, int index);
static int GStringMgr_SplitCount(const char* strIn, char* sep);
static void GStringMgr_Replace(const char* strIn, char* strOut, const char* pattern, const char* replace);
//===============================================
GStringMgrO* GStringMgr_New() {
    GStringMgrO* lObj = (GStringMgrO*)malloc(sizeof(GStringMgrO));
    
    lObj->Copy = GStringMgr_Copy;
    lObj->ToUpper = GStringMgr_ToUpper;
    lObj->ToLower = GStringMgr_ToLower;
    lObj->Delete = GStringMgr_Delete;
    lObj->Trim = GStringMgr_Trim;
    lObj->SplitGet = GStringMgr_SplitGet;
    lObj->SplitCount = GStringMgr_SplitCount;
    lObj->Replace = GStringMgr_Replace;
    return lObj; 
}
//===============================================
void GStringMgr_Delete() {

}
//===============================================
GStringMgrO* GStringMgr() {
    if(m_GStringMgrO == 0) {
        m_GStringMgrO = GStringMgr_New();
    }
    return m_GStringMgrO;
}
//===============================================
static char* GStringMgr_Copy(const char* strIn) {
    int lSize = strlen(strIn);
    char* lStrOut = (char*)malloc(sizeof(char)*(lSize+1));
    strcpy(lStrOut, strIn);
}
//===============================================
static void GStringMgr_ToUpper(const char* strIn, char* strOut) {
    int lSize = strlen(strIn);
    char strIn2[B_STRING_SIZE+1];
    if(strlen(strIn) > B_STRING_SIZE) {printf("[GStringMgr] : erreur taille"); exit(0);}
    strcpy(strIn2, strIn);

    for(int i = 0; i < lSize; i ++) {
        strOut[i] = toupper(strIn2[i]);
    }
    strOut[lSize] = 0;
}
//===============================================
static void GStringMgr_ToLower(const char* strIn, char* strOut) {
    int lSize = strlen(strIn);
    char strIn2[B_STRING_SIZE+1];
    if(strlen(strIn) > B_STRING_SIZE) {printf("[GStringMgr] : erreur taille"); exit(0);}
    strcpy(strIn2, strIn);

    for(int i = 0; i < lSize; i ++) {
        strOut[i] = tolower(strIn2[i]);
    }
    strOut[lSize] = 0;
}
//===============================================
static void GStringMgr_Trim(const char* strIn, char* strOut) {
    int lPos = 0;
    int lLeft = 0;
    int lFlag = 0;
    char strIn2[B_STRING_SIZE+1];
    if(strlen(strIn) > B_STRING_SIZE) {printf("[GStringMgr] : erreur taille"); exit(0);}
    strcpy(strIn2, strIn);

    while(strIn2[lPos] != 0) {
        if(lFlag == 0) {
            char lChar = strIn2[lPos];
            if(isspace(lChar) == 0) lFlag = 1;
            else lPos++;
        }
        if(lFlag == 1) {
            lLeft = lPos;
            break;
        }
    }
    lPos = strlen(strIn2) - 1;
    int lRight = 0;
    lFlag = 0;
    while(lPos >= 0) {
        if(lFlag == 0) {
            char lChar = strIn2[lPos];
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
        strOut[lOut] = strIn2[lPos];
    }
    strOut[lOut] = 0;
}
//===============================================
static void GStringMgr_SplitGet(const char* strIn, char* strOut, char* sep, int index) {
    int lPos = 0;
    int lOut = 0;
    int lCount = 0;
    int lFlag = 0;
    char strIn2[B_STRING_SIZE+1];
    if(strlen(strIn) > B_STRING_SIZE) {printf("[GStringMgr] : erreur taille"); exit(0);}
    strcpy(strIn2, strIn);

    while(strIn2[lPos] != 0) {
        if(lFlag == 0) {
            if(lCount == index) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) break;
            strOut[lOut] = lChar;
            lPos++; lOut++;
        }
        if(lFlag == 2) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) lCount++;
            lPos++;
            lFlag = 0;
        }
    }
    strOut[lOut] = 0;
}
//===============================================
static int GStringMgr_SplitCount(const char* strIn, char* sep) {
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
static void GStringMgr_Replace(const char* strIn, char* strOut, const char* pattern, const char* replace) {
    int lFlag = 0;
    int lPos = 0;
    int lOut = 0;
    char* lPattern = 0;
    int lSize = strlen(pattern);
    char lBuffer[B_STRING_SIZE+1];
    char strIn2[B_STRING_SIZE+1];
    if(strlen(strIn) > B_STRING_SIZE) {printf("[GStringMgr] : erreur taille"); exit(0);}
    strcpy(strIn2, strIn);
    
    while(strIn2[lPos] != 0) {
        if(lFlag == 0) {
            lPattern = strstr(&strIn2[lPos], pattern);
            if(lPattern == 0) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            sprintf(lBuffer, "%s", &strIn2[lPos]);
            lOut += sprintf(&strOut[lOut], "%s", lBuffer);
            break;
        }
        if(lFlag == 2) {
            int lPosIn = lPos;
            lPos = (lPattern - strIn2);
            int lSizeIn = lPos - lPosIn;
            memcpy(lBuffer, &strIn2[lPosIn], lSizeIn); lBuffer[lSizeIn] = 0;
            lOut += sprintf(&strOut[lOut], "%s", lBuffer);
            lFlag = 3;
        }
        if(lFlag == 3) {
            lPos += lSize;
            lOut += sprintf(&strOut[lOut], "%s", replace);
            lFlag = 0;
        }
    }
}
//===============================================
