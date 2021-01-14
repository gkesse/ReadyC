//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GInclude.h"
//===============================================
#define GDECLARE_MAP(GPREFIX, GKEY, GVALUE) \
        typedef struct _GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE; \
        typedef struct _GMapO_##GPREFIX##_##GKEY##_##GVALUE GMapO_##GPREFIX##_##GKEY##_##GVALUE; \
        typedef int (*GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE)(GKEY key1, GKEY key2); \
        typedef void (*GMAP_EQUAL_##GPREFIX##_##GKEY##_##GVALUE)(GKEY key, GVALUE value); \
        \
        struct _GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE { \
            GKEY m_key; \
            GVALUE m_value; \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* m_next; \
        }; \
        \
        struct _GMapO_##GPREFIX##_##GKEY##_##GVALUE { \
            void (*Delete)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
            void (*SetData)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
            GVALUE (*GetData)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
            void (*Clear)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
            void (*Remove)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
            int (*Size)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
            void (*Show)(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GMAP_EQUAL_##GPREFIX##_##GKEY##_##GVALUE show); \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* m_head; \
        }; \
        \
        GMapO_##GPREFIX##_##GKEY##_##GVALUE* GMap_New_##GPREFIX##_##GKEY##_##GVALUE(); \
        static void GMap_Delete_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
        static void GMap_Clear_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
        static void GMap_Remove_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
        static void GMap_RemoveNode_##GPREFIX##_##GKEY##_##GVALUE(GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* node); \
        static void GMap_SetData_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
        static GVALUE GMap_GetData_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal); \
        static int GMap_Size_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj); \
        static void GMap_Show_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GMAP_EQUAL_##GPREFIX##_##GKEY##_##GVALUE show);
//===============================================
#define GDEFINE_MAP(GPREFIX, GKEY, GVALUE) \
        \
        GMapO_##GPREFIX##_##GKEY##_##GVALUE* GMap_New_##GPREFIX##_##GKEY##_##GVALUE() { \
            GMapO_##GPREFIX##_##GKEY##_##GVALUE* lObj = (GMapO_##GPREFIX##_##GKEY##_##GVALUE*)malloc(sizeof(GMapO_##GPREFIX##_##GKEY##_##GVALUE)); \
            \
            lObj->Delete = GMap_Delete_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->Clear = GMap_Clear_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->Remove = GMap_Remove_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->SetData = GMap_SetData_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->GetData = GMap_GetData_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->Size = GMap_Size_##GPREFIX##_##GKEY##_##GVALUE; \
            lObj->Show = GMap_Show_##GPREFIX##_##GKEY##_##GVALUE; \
            \
            lObj->m_head = 0; \
            return lObj; \
        } \
        \
        static void GMap_Delete_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj) { \
            if(obj != 0) { \
                obj->Clear(obj); \
                free(obj); \
            } \
        } \
        \
        static void GMap_Clear_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj) { \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            while(lNext != 0) { \
                GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lPrevious = lNext; \
                lNext = lNext->m_next; \
                GMap_RemoveNode_##GPREFIX##_##GKEY##_##GVALUE(lPrevious); \
            } \
            obj->m_head = 0; \
        } \
        \
        static void GMap_Remove_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal) { \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lPrevious = 0; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                int lEqual = 0; \
                if(equal == 0) lEqual = (lKey == key) ? 1 : 0; \
                else lEqual = equal(lKey, key); \
                if(lEqual == 1) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    GMap_RemoveNode_##GPREFIX##_##GKEY##_##GVALUE(lNext); \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
        } \
        \
        static void GMap_RemoveNode_##GPREFIX##_##GKEY##_##GVALUE(GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* node) { \
            if(node != 0) { \
                free(node); \
            } \
        } \
        \
        static void GMap_SetData_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal) { \
            if(obj == 0) {printf("[GMap] error SetData()\n");  exit(0);} \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lPrevious = 0; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                int lEqual = 0; \
                if(equal == 0) lEqual = (lKey == key) ? 1 : 0; \
                else lEqual = equal(lKey, key); \
                if(lEqual == 1) { \
                    free(lNext->m_value); \
                    lNext->m_value = value; \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
            \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNode = (GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE*)malloc(sizeof(GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE)); \
            lNode->m_key = key; \
            lNode->m_value = value; \
            lNode->m_next = 0; \
            \
            if(lPrevious == 0) obj->m_head = lNode; \
            else lPrevious->m_next = lNode; \
        }\
        \
        static GVALUE GMap_GetData_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GKEY key, GMAP_EQUAL_KEY_##GPREFIX##_##GKEY##_##GVALUE equal) { \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                GVALUE lValue = lNext->m_value; \
                int lEqual = 0; \
                if(equal == 0) lEqual = (lKey == key) ? 1 : 0; \
                else lEqual = equal(lKey, key); \
                if(lEqual == 1) return lValue; \
                lNext = lNext->m_next; \
            } \
            return 0; \
        } \
        \
        static int GMap_Size_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj) { \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            int lSize = 0; \
            \
            while(lNext != 0) { \
                lSize++; \
                lNext = lNext->m_next; \
            } \
            return lSize; \
        } \
        \
        static void GMap_Show_##GPREFIX##_##GKEY##_##GVALUE(GMapO_##GPREFIX##_##GKEY##_##GVALUE* obj, GMAP_EQUAL_##GPREFIX##_##GKEY##_##GVALUE show) { \
            GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE* lNext = obj->m_head; \
            \
            while(lNext != 0) { \
                GKEY lKey = lNext->m_key; \
                GVALUE lValue = lNext->m_value; \
                show(lKey, lValue); \
                lNext = lNext->m_next; \
            } \
        }
//===============================================
#define GMap_New(GPREFIX, GKEY, GVALUE) \
        GMap_New_##GPREFIX##_##GKEY##_##GVALUE
//===============================================
#define GMapO(GPREFIX, GKEY, GVALUE) \
        GMapO_##GPREFIX##_##GKEY##_##GVALUE
//===============================================
#define GMapNodeO(GPREFIX, GKEY, GVALUE) \
        GMapNodeO_##GPREFIX##_##GKEY##_##GVALUE
//===============================================
typedef char* GCHAR_PTR;
typedef void* GVOID_PTR;
//===============================================
#if defined(_GMAP_EQUAL_CHAR_)
//===============================================
static int GMAP_EQUAL_CHAR(void* key1, void* key2);
//===============================================
static int GMAP_EQUAL_CHAR(void* key1, void* key2) {
    int lStrcmp = strcmp((char*)key1, (char*)key2);
    if(lStrcmp == 0) return 1;
    return 0;
}
//===============================================
#endif
//===============================================
#if defined(_GMAP_SHOW_CHAR_)
//===============================================
static void GMAP_SHOW_CHAR(void* key, void* value);
//===============================================
static void GMAP_SHOW_CHAR(void* key, void* value) {
    printf("%s = %s\n", (char*)key, (char*)value);
}
//===============================================
#endif
//===============================================
#endif
//===============================================
