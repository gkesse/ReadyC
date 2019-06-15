//===============================================
#include "GConfigNormal.h"
//===============================================
static GConfigO* m_GConfigNormalO = 0;
//===============================================
static void GConfigNormal_Clear();
static void GConfigNormal_Remove(char* key);
static void GConfigNormal_RemoveNode(GConfigNodeO* node);
static void GConfigNormal_SetData(char* key, char* value);
static char* GConfigNormal_GetData(char* key);
static int GConfigNormal_Size();
static void GConfigNormal_Show();
//===============================================
GConfigO* GConfigNormal_New() {
    GConfigO* lParent = GConfig_New();
    GConfigNormalO* lChild = (GConfigNormalO*)malloc(sizeof(GConfigNormalO));
    //
    lChild->m_parent = lParent;
    lChild->m_head = 0;
    //
    lParent->m_child = lChild;
    lParent->Delete = GConfigNormal_Delete;
    lParent->Clear = GConfigNormal_Clear;
    lParent->Remove = GConfigNormal_Remove;
    lParent->SetData = GConfigNormal_SetData;
    lParent->GetData = GConfigNormal_GetData;
    lParent->Size = GConfigNormal_Size;
    lParent->Show = GConfigNormal_Show;
    return lParent;
}
//===============================================
void GConfigNormal_Delete() {
    GConfigNormal_Clear();
    GConfig_Delete();
    m_GConfigNormalO = 0;
}
//===============================================
GConfigO* GConfigNormal() {
    if(m_GConfigNormalO == 0) {
        m_GConfigNormalO = GConfigNormal_New();
    }
    return m_GConfigNormalO;
}
//===============================================
static void GConfigNormal_Clear() {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;

    while(lNext != 0) {
        GConfigNodeO* lPrevious = lNext;
        lNext = lNext->m_next;
        GConfigNormal_RemoveNode(lPrevious);
    }
    lConfigNormal->m_head = 0;
}
//===============================================
static void GConfigNormal_Remove(char* key) {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;
    GConfigNodeO* lPrevious = 0;

    while(lNext != 0) {
        int lStrcmp = strcmp(lNext->m_key, key);
        if(lStrcmp == 0) {
            if(lPrevious == 0) lConfigNormal->m_head = lNext->m_next;
            else lPrevious->m_next = lNext->m_next;
            GConfigNormal_RemoveNode(lNext);
            return;
        }
        lPrevious = lNext;
        lNext = lNext->m_next;
    }
}
//===============================================
static void GConfigNormal_RemoveNode(GConfigNodeO* node) {
    if(node != 0) {
        free(node);
    }
}
//===============================================
static void GConfigNormal_SetData(char* key, char* value) {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;
    GConfigNodeO* lPrevious = 0;

    while(lNext != 0) {
        int lStrcmp = strcmp(lNext->m_key, key);
        if(lStrcmp == 0) {
            lNext->m_value = value;
            return;
        }
        lPrevious = lNext;
        lNext = lNext->m_next;
    }

    GConfigNodeO* lNode = (GConfigNodeO*)malloc(sizeof(GConfigNodeO));
    lNode->m_key = key;
    lNode->m_value = value;
    lNode->m_next = 0;

    if(lPrevious == 0) lConfigNormal->m_head = lNode;
    else lPrevious->m_next = lNode;
}
//===============================================
static char* GConfigNormal_GetData(char* key) {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;

    while(lNext != 0) {
        int lStrcmp = strcmp(lNext->m_key, key);
        if(lStrcmp == 0) {
            return lNext->m_value;
        }
        lNext = lNext->m_next;
    }
    return 0;
}
//===============================================
static int GConfigNormal_Size() {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;
    int lSize = 0;

    while(lNext != 0) {
        lSize++;
        lNext = lNext->m_next;
    }
    printf("Size: %d\n", lSize);
    return lSize;
}
//===============================================
static void GConfigNormal_Show() {
    GConfigNormalO* lConfigNormal = m_GConfigNormalO->m_child;
    GConfigNodeO* lNext = lConfigNormal->m_head;

    while(lNext != 0) {
        char* lKey = lNext->m_key;
        char* lValue = lNext->m_value;
        printf("%s = %s\n", lKey, lValue);
        lNext = lNext->m_next;
    }
}
//===============================================
