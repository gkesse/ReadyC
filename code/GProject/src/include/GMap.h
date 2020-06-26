//===============================================
#ifndef _GMap_
#define _GMap_
//===============================================
#include "GInclude.h"
//===============================================
#define GDECLARE_MAP(GKEY, GVALUE, GTYPE) \
		typedef struct _GMapNodeO_##GTYPE GMapNodeO_##GTYPE; \
		typedef struct _GMapO_##GTYPE GMapO_##GTYPE; \
		typedef int (*GMAP_EQUAL_KEY_##GTYPE)(GKEY key1, GKEY key2); \
		typedef void (*GMAP_SHOWL_##GTYPE)(GKEY key, GVALUE value); \
		\
		struct _GMapNodeO_##GTYPE { \
			GKEY m_key; \
			GVALUE m_value; \
			GMapNodeO_##GTYPE* m_next; \
		}; \
		\
		struct _GMapO_##GTYPE { \
			void (*Delete)(GMapO_##GTYPE* obj); \
			void (*SetData)(GMapO_##GTYPE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GTYPE equal); \
			GVALUE (*GetData)(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal); \
			void (*Clear)(GMapO_##GTYPE* obj); \
			void (*Remove)(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal); \
			int (*Size)(GMapO_##GTYPE* obj); \
			void (*Show)(GMapO_##GTYPE* obj, GMAP_SHOWL_##GTYPE show); \
			GMapNodeO_##GTYPE* m_head; \
		}; \
		\
		GMapO_##GTYPE* GMap_New_##GTYPE(); \
		static void GMap_Delete_##GTYPE(GMapO_##GTYPE* obj); \
		static void GMap_Clear_##GTYPE(GMapO_##GTYPE* obj); \
		static void GMap_Remove_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal); \
		static void GMap_RemoveNode_##GTYPE(GMapNodeO_##GTYPE* node); \
		static void GMap_SetData_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GTYPE equal); \
		static GVALUE GMap_GetData_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal); \
		static int GMap_Size_##GTYPE(GMapO_##GTYPE* obj); \
		static void GMap_Show_##GTYPE(GMapO_##GTYPE* obj, GMAP_SHOWL_##GTYPE show);
//===============================================
#define GDEFINE_MAP(GKEY, GVALUE, GTYPE) \
		\
		GMapO_##GTYPE* GMap_New_##GTYPE() { \
			GMapO_##GTYPE* lObj = (GMapO_##GTYPE*)malloc(sizeof(GMapO_##GTYPE)); \
			\
			lObj->Delete = GMap_Delete_##GTYPE; \
			lObj->Clear = GMap_Clear_##GTYPE; \
			lObj->Remove = GMap_Remove_##GTYPE; \
			lObj->SetData = GMap_SetData_##GTYPE; \
			lObj->GetData = GMap_GetData_##GTYPE; \
			lObj->Size = GMap_Size_##GTYPE; \
			lObj->Show = GMap_Show_##GTYPE; \
			\
			lObj->m_head = 0; \
			return lObj; \
		} \
		\
		static void GMap_Delete_##GTYPE(GMapO_##GTYPE* obj) { \
			if(obj != 0) { \
				obj->Clear(obj); \
				free(obj); \
			} \
		} \
		\
		static void GMap_Clear_##GTYPE(GMapO_##GTYPE* obj) { \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			while(lNext != 0) { \
				GMapNodeO_##GTYPE* lPrevious = lNext; \
				lNext = lNext->m_next; \
				GMap_RemoveNode_##GTYPE(lPrevious); \
			} \
			obj->m_head = 0; \
		} \
		\
		static void GMap_Remove_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal) { \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			GMapNodeO_##GTYPE* lPrevious = 0; \
			\
			while(lNext != 0) { \
				GKEY lKey = lNext->m_key; \
				int lEqual = FALSE; \
				if(equal == 0) lEqual = (lKey == key) ? TRUE : FALSE; \
				else lEqual = equal(lKey, key); \
				if(lEqual == TRUE) { \
					if(lPrevious == 0) obj->m_head = lNext->m_next; \
					else lPrevious->m_next = lNext->m_next; \
					GMap_RemoveNode_##GTYPE(lNext); \
					return; \
				} \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
			} \
		} \
		\
		static void GMap_RemoveNode_##GTYPE(GMapNodeO_##GTYPE* node) { \
			if(node != 0) { \
				free(node); \
			} \
		} \
		\
		static void GMap_SetData_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GVALUE value, GMAP_EQUAL_KEY_##GTYPE equal) { \
			if(obj == 0) {printf("[ GMap ] Error Map None\n");  exit(0);} \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			GMapNodeO_##GTYPE* lPrevious = 0; \
			\
			while(lNext != 0) { \
				GKEY lKey = lNext->m_key; \
				BOOL lEqual = FALSE; \
				if(equal == 0) lEqual = (lKey == key) ? TRUE : FALSE; \
				else lEqual = equal(lKey, key); \
				if(lEqual == TRUE) { \
					lNext->m_value = value; \
					return; \
				} \
				lPrevious = lNext; \
				lNext = lNext->m_next; \
			} \
			\
			GMapNodeO_##GTYPE* lNode = (GMapNodeO_##GTYPE*)malloc(sizeof(GMapNodeO_##GTYPE)); \
			lNode->m_key = key; \
			lNode->m_value = value; \
			lNode->m_next = 0; \
			\
			if(lPrevious == 0) obj->m_head = lNode; \
			else lPrevious->m_next = lNode; \
		}\
		\
		static GVALUE GMap_GetData_##GTYPE(GMapO_##GTYPE* obj, GKEY key, GMAP_EQUAL_KEY_##GTYPE equal) { \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			\
			while(lNext != 0) { \
				GKEY lKey = lNext->m_key; \
				GVALUE lValue = lNext->m_value; \
				int lEqual = FALSE; \
				if(equal == 0) lEqual = (lKey == key) ? TRUE : FALSE; \
				else lEqual = equal(lKey, key); \
				if(lEqual == TRUE) return lValue; \
				lNext = lNext->m_next; \
			} \
			return 0; \
		} \
		\
		static int GMap_Size_##GTYPE(GMapO_##GTYPE* obj) { \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			int lSize = 0; \
			\
			while(lNext != 0) { \
				lSize++; \
				lNext = lNext->m_next; \
			} \
			printf("[ GMap ] Size: %d\n", lSize); \
			return lSize; \
		} \
		\
		static void GMap_Show_##GTYPE(GMapO_##GTYPE* obj, GMAP_SHOWL_##GTYPE show) { \
			GMapNodeO_##GTYPE* lNext = obj->m_head; \
			\
			while(lNext != 0) { \
				GKEY lKey = lNext->m_key; \
				GVALUE lValue = lNext->m_value; \
				show(lKey, lValue); \
				lNext = lNext->m_next; \
			} \
		}
//===============================================
#define GMapO(GTYPE) \
		GMapO_##GTYPE
//===============================================
#define GMapNodeO(GTYPE) \
		GMapNodeO_##GTYPE
//===============================================
#endif
//===============================================
