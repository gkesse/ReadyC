//===============================================
#ifndef _GList_
#define _GList_
//===============================================
#include "GInclude.h"
//===============================================
#define GDECLARE_LIST(GPREFIX, GDATA) \
        typedef struct _GListNodeO_##GPREFIX##_##GDATA GListNodeO_##GPREFIX##_##GDATA; \
        typedef struct _GListO_##GPREFIX##_##GDATA GListO_##GPREFIX##_##GDATA; \
        typedef int (*GLIST_EQUAL_DATA_##GPREFIX##_##GDATA)(GDATA data1, char* data2); \
        typedef void (*GLIST_SHOW_##GPREFIX##_##GDATA)(int index, GDATA data); \
        typedef void (*GLIST_REMOVE_##GPREFIX##_##GDATA)(GDATA data); \
        \
        struct _GListNodeO_##GPREFIX##_##GDATA { \
            GDATA m_data; \
            GListNodeO_##GPREFIX##_##GDATA* m_next; \
        }; \
        \
        struct _GListO_##GPREFIX##_##GDATA { \
            void (*Delete)(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            void (*Clear)(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            void (*RemoveIndex)(GListO_##GPREFIX##_##GDATA* obj, int index, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            void (*RemoveData)(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            void (*RemoveDataAll)(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            void (*AddData)(GListO_##GPREFIX##_##GDATA* obj, GDATA data); \
            void (*SetData)(GListO_##GPREFIX##_##GDATA* obj, int index, GDATA data, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
            GDATA (*GetData)(GListO_##GPREFIX##_##GDATA* obj, int index); \
            int (*CountData)(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal); \
            int (*Size)(GListO_##GPREFIX##_##GDATA* obj); \
            void (*Show)(GListO_##GPREFIX##_##GDATA* obj, GLIST_SHOW_##GPREFIX##_##GDATA show); \
            GListNodeO_##GPREFIX##_##GDATA* m_head; \
        }; \
        \
        GListO_##GPREFIX##_##GDATA* GList_New_##GPREFIX##_##GDATA(); \
        static void GList_Delete_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_Clear_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_RemoveIndex_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_RemoveData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_RemoveDataAll_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_RemoveNode_##GPREFIX##_##GDATA(GListNodeO_##GPREFIX##_##GDATA* node, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static void GList_AddData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GDATA data); \
        static void GList_SetData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index, GDATA data, GLIST_REMOVE_##GPREFIX##_##GDATA remove); \
        static GDATA GList_GetData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index); \
        static int GList_CountData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal); \
        static int GList_Size_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj); \
        static void GList_Show_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_SHOW_##GPREFIX##_##GDATA show);
//===============================================
#define GDEFINE_LIST(GPREFIX, GDATA) \
        \
        GListO_##GPREFIX##_##GDATA* GList_New_##GPREFIX##_##GDATA() { \
            GListO_##GPREFIX##_##GDATA* lObj = (GListO_##GPREFIX##_##GDATA*)malloc(sizeof(GListO_##GPREFIX##_##GDATA)); \
            \
            lObj->Delete = GList_Delete_##GPREFIX##_##GDATA; \
            lObj->Clear = GList_Clear_##GPREFIX##_##GDATA; \
            lObj->RemoveIndex = GList_RemoveIndex_##GPREFIX##_##GDATA; \
            lObj->RemoveData = GList_RemoveData_##GPREFIX##_##GDATA; \
            lObj->RemoveDataAll = GList_RemoveDataAll_##GPREFIX##_##GDATA; \
            lObj->AddData = GList_AddData_##GPREFIX##_##GDATA; \
            lObj->SetData = GList_SetData_##GPREFIX##_##GDATA; \
            lObj->GetData = GList_GetData_##GPREFIX##_##GDATA; \
            lObj->CountData = GList_CountData_##GPREFIX##_##GDATA; \
            lObj->Size = GList_Size_##GPREFIX##_##GDATA; \
            lObj->Show = GList_Show_##GPREFIX##_##GDATA; \
            \
            lObj->m_head = 0; \
            return lObj; \
        } \
        \
        static void GList_Delete_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GList_Clear_##GPREFIX##_##GDATA(obj, remove); \
            free(obj); \
        } \
        \
        static void GList_Clear_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            while(lNext != 0) { \
                GListNodeO_##GPREFIX##_##GDATA* lPrevious = lNext; \
                lNext = lNext->m_next; \
                GList_RemoveNode_##GPREFIX##_##GDATA(lPrevious, remove); \
            } \
            obj->m_head = 0; \
        } \
        \
        static void GList_RemoveIndex_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GPREFIX##_##GDATA* lPrevious = 0; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                if(lIndex == index) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    GList_RemoveNode_##GPREFIX##_##GDATA(lNext, remove); \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
        } \
        \
        static void GList_RemoveData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GPREFIX##_##GDATA* lPrevious = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                int lEqual = equal(lData, data); \
                if(lEqual == TRUE) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    GList_RemoveNode_##GPREFIX##_##GDATA(lNext, remove); \
                    return; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
        } \
        \
        static void GList_RemoveDataAll_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GPREFIX##_##GDATA* lPrevious = 0; \
            GListNodeO_##GPREFIX##_##GDATA* lNode = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                int lEqual = equal(lData, data); \
                if(lEqual == TRUE) { \
                    if(lPrevious == 0) obj->m_head = lNext->m_next; \
                    else lPrevious->m_next = lNext->m_next; \
                    lNode = lNext; \
                    lNext = lNext->m_next; \
                    GList_RemoveNode_##GPREFIX##_##GDATA(lNode, remove); \
                    continue; \
                } \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
        } \
        \
        static void GList_RemoveNode_##GPREFIX##_##GDATA(GListNodeO_##GPREFIX##_##GDATA* node, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GDATA lData = node->m_data; \
            if(remove == 0) free(lData); \
            else remove(lData); \
            free(node); \
        } \
        \
        static void GList_AddData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GDATA data) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            GListNodeO_##GPREFIX##_##GDATA* lPrevious = 0; \
            \
            while(lNext != 0) { \
                lPrevious = lNext; \
                lNext = lNext->m_next; \
            } \
            \
            GListNodeO_##GPREFIX##_##GDATA* lNode = (GListNodeO_##GPREFIX##_##GDATA*)malloc(sizeof(GListNodeO_##GPREFIX##_##GDATA)); \
            lNode->m_data = data; \
            lNode->m_next = 0; \
            \
            if(lPrevious == 0) obj->m_head = lNode; \
            else lPrevious->m_next = lNode; \
        }\
        \
        static void GList_SetData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index, GDATA data, GLIST_REMOVE_##GPREFIX##_##GDATA remove) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                if(lIndex == index) { \
                    GDATA lData = lNext->m_data; \
                    if(remove == 0) free(lData); \
                    else remove(lData); \
                    lNext->m_data = data; \
                    return; \
                } \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
            \
            \
        }\
        \
        static GDATA GList_GetData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, int index) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                if(lIndex == index) return lData; \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
            return 0; \
        } \
        \
        static int GList_CountData_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, char* data, GLIST_EQUAL_DATA_##GPREFIX##_##GDATA equal) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            int lCount = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                int lEqual = equal(lData, data); \
                if(lEqual == TRUE) { \
                    lCount++; \
                } \
                lNext = lNext->m_next; \
            } \
            return lCount; \
        } \
        \
        static int GList_Size_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            int lSize = 0; \
            \
            while(lNext != 0) { \
                lSize++; \
                lNext = lNext->m_next; \
            } \
            return lSize; \
        } \
        \
        static void GList_Show_##GPREFIX##_##GDATA(GListO_##GPREFIX##_##GDATA* obj, GLIST_SHOW_##GPREFIX##_##GDATA show) { \
            GListNodeO_##GPREFIX##_##GDATA* lNext = obj->m_head; \
            int lIndex = 0; \
            \
            while(lNext != 0) { \
                GDATA lData = lNext->m_data; \
                show(lIndex, lData); \
                lNext = lNext->m_next; \
                lIndex++; \
            } \
        }
//===============================================
#define GList_New(GPREFIX, GDATA) \
        GList_New_##GPREFIX##_##GDATA
//===============================================
#define GListO(GPREFIX, GDATA) \
        GListO_##GPREFIX##_##GDATA
//===============================================
#define GListNodeO(GPREFIX, GDATA) \
        GListNodeO_##GPREFIX##_##GDATA
//===============================================
typedef char* GCHAR_PTR;
typedef void* GVOID_PTR;
//===============================================
#if defined(_GLIST_SHOW_CHAR_)
//===============================================
static void GLIST_SHOW_CHAR(int index, void* value);
//===============================================
static void GLIST_SHOW_CHAR(int index, void* value) {
    printf("%20s", (char*)value);
}
//===============================================
#endif
//===============================================
#endif
//===============================================