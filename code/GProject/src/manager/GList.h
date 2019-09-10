//===============================================
#ifndef _GList_
#define _GList_
//===============================================
#include "GInclude.h"
//===============================================
#define GDECLARE_LIST(GDATA, GTYPE) \
		typedef struct _GListNodeO_##GTYPE GListNodeO_##GTYPE; \
		typedef struct _GListO_##GTYPE GListO_##GTYPE; \
        typedef int (*GLIST_EQUAL_DATA_##GTYPE)(GDATA data1, char* data2); \
		typedef void (*GLIST_SHOW_##GTYPE)(int index, GDATA data); \
		typedef void (*GLIST_REMOVE_##GTYPE)(GDATA data); \
		\
		struct _GListNodeO_##GTYPE { \
			GDATA m_data; \
			GListNodeO_##GTYPE* m_next; \
		}; \
		\
		struct _GListO_##GTYPE { \
			void (*Delete)(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove); \
			void (*Clear)(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove); \
			void (*RemoveIndex)(GListO_##GTYPE* obj, int index, GLIST_REMOVE_##GTYPE remove); \
			void (*RemoveData)(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove); \
			void (*RemoveDataAll)(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove); \
			void (*AddData)(GListO_##GTYPE* obj, GDATA data); \
			void (*SetData)(GListO_##GTYPE* obj, int index, GDATA data, GLIST_REMOVE_##GTYPE remove); \
			GDATA (*GetData)(GListO_##GTYPE* obj, int index); \
			int (*CountData)(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal); \
			int (*Size)(GListO_##GTYPE* obj); \
			void (*Show)(GListO_##GTYPE* obj, GLIST_SHOW_##GTYPE show); \
			GListNodeO_##GTYPE* m_head; \
		}; \
        \
		GListO_##GTYPE* GList_New_##GTYPE(); \
		static void GList_Delete_##GTYPE(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove); \
		static void GList_Clear_##GTYPE(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove); \
		static void GList_RemoveIndex_##GTYPE(GListO_##GTYPE* obj, int index, GLIST_REMOVE_##GTYPE remove); \
		static void GList_RemoveData_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove); \
		static void GList_RemoveDataAll_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove); \
		static void GList_RemoveNode_##GTYPE(GListNodeO_##GTYPE* node, GLIST_REMOVE_##GTYPE remove); \
		static void GList_AddData_##GTYPE(GListO_##GTYPE* obj, GDATA data); \
		static void GList_SetData_##GTYPE(GListO_##GTYPE* obj, int index, GDATA data, GLIST_REMOVE_##GTYPE remove); \
		static GDATA GList_GetData_##GTYPE(GListO_##GTYPE* obj, int index); \
		static int GList_CountData_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal); \
		static int GList_Size_##GTYPE(GListO_##GTYPE* obj); \
		static void GList_Show_##GTYPE(GListO_##GTYPE* obj, GLIST_SHOW_##GTYPE show);
//===============================================
#define GDEFINE_LIST(GDATA, GTYPE) \
		\
		GListO_##GTYPE* GList_New_##GTYPE() { \
			GListO_##GTYPE* lObj = (GListO_##GTYPE*)malloc(sizeof(GListO_##GTYPE)); \
			\
			lObj->Delete = GList_Delete_##GTYPE; \
			lObj->Clear = GList_Clear_##GTYPE; \
			lObj->RemoveIndex = GList_RemoveIndex_##GTYPE; \
			lObj->RemoveData = GList_RemoveData_##GTYPE; \
			lObj->RemoveDataAll = GList_RemoveDataAll_##GTYPE; \
			lObj->AddData = GList_AddData_##GTYPE; \
			lObj->SetData = GList_SetData_##GTYPE; \
			lObj->GetData = GList_GetData_##GTYPE; \
			lObj->CountData = GList_CountData_##GTYPE; \
			lObj->Size = GList_Size_##GTYPE; \
			lObj->Show = GList_Show_##GTYPE; \
			\
			lObj->m_head = 0; \
			return lObj; \
		} \
		\
		static void GList_Delete_##GTYPE(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove) { \
            GList_Clear_##GTYPE(obj, remove); \
            free(obj); \
		} \
		\
		static void GList_Clear_##GTYPE(GListO_##GTYPE* obj, GLIST_REMOVE_##GTYPE remove) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			while(lNext != 0) { \
				GListNodeO_##GTYPE* lPrevious = lNext; \
				lNext = lNext->m_next; \
				GList_RemoveNode_##GTYPE(lPrevious, remove); \
			} \
			obj->m_head = 0; \
		} \
		\
		static void GList_RemoveIndex_##GTYPE(GListO_##GTYPE* obj, int index, GLIST_REMOVE_##GTYPE remove) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			GListNodeO_##GTYPE* lPrevious = 0; \
            int lIndex = 0; \
			\
			while(lNext != 0) { \
				if(lIndex == index) { \
					if(lPrevious == 0) obj->m_head = lNext->m_next; \
					else lPrevious->m_next = lNext->m_next; \
					GList_RemoveNode_##GTYPE(lNext, remove); \
					return; \
				} \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
                lIndex++; \
			} \
		} \
        \
		static void GList_RemoveData_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			GListNodeO_##GTYPE* lPrevious = 0; \
			\
			while(lNext != 0) { \
				GDATA lData = lNext->m_data; \
				int lEqual = equal(lData, data); \
				if(lEqual == TRUE) { \
					if(lPrevious == 0) obj->m_head = lNext->m_next; \
					else lPrevious->m_next = lNext->m_next; \
					GList_RemoveNode_##GTYPE(lNext, remove); \
					return; \
				} \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
			} \
		} \
        \
		static void GList_RemoveDataAll_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal, GLIST_REMOVE_##GTYPE remove) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			GListNodeO_##GTYPE* lPrevious = 0; \
			GListNodeO_##GTYPE* lNode = 0; \
			\
			while(lNext != 0) { \
				GDATA lData = lNext->m_data; \
				int lEqual = equal(lData, data); \
				if(lEqual == TRUE) { \
					if(lPrevious == 0) obj->m_head = lNext->m_next; \
					else lPrevious->m_next = lNext->m_next; \
                    lNode = lNext; \
                    lNext = lNext->m_next; \
					GList_RemoveNode_##GTYPE(lNode, remove); \
					continue; \
				} \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
			} \
		} \
        \
		static void GList_RemoveNode_##GTYPE(GListNodeO_##GTYPE* node, GLIST_REMOVE_##GTYPE remove) { \
            GDATA lData = node->m_data; \
            if(remove == 0) free(lData); \
            else remove(lData); \
            free(node); \
		} \
		\
		static void GList_AddData_##GTYPE(GListO_##GTYPE* obj, GDATA data) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			GListNodeO_##GTYPE* lPrevious = 0; \
			\
			while(lNext != 0) { \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
			} \
			\
			GListNodeO_##GTYPE* lNode = (GListNodeO_##GTYPE*)malloc(sizeof(GListNodeO_##GTYPE)); \
			lNode->m_data = data; \
			lNode->m_next = 0; \
			\
			if(lPrevious == 0) obj->m_head = lNode; \
			else lPrevious->m_next = lNode; \
		}\
		\
		static void GList_SetData_##GTYPE(GListO_##GTYPE* obj, int index, GDATA data, GLIST_REMOVE_##GTYPE remove) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
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
		static GDATA GList_GetData_##GTYPE(GListO_##GTYPE* obj, int index) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
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
		static int GList_CountData_##GTYPE(GListO_##GTYPE* obj, char* data, GLIST_EQUAL_DATA_##GTYPE equal) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
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
		static int GList_Size_##GTYPE(GListO_##GTYPE* obj) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
			int lSize = 0; \
			\
			while(lNext != 0) { \
				lSize++; \
				lNext = lNext->m_next; \
			} \
			return lSize; \
		} \
		\
		static void GList_Show_##GTYPE(GListO_##GTYPE* obj, GLIST_SHOW_##GTYPE show) { \
			GListNodeO_##GTYPE* lNext = obj->m_head; \
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
#define GListO(GTYPE) \
		GListO_##GTYPE
//===============================================
#define GListNodeO(GTYPE) \
		GListNodeO_##GTYPE
//===============================================
#endif
//===============================================
