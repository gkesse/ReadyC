//===============================================
#include "GCcv.h"
#include "GMap.h"
#include "GDebug.h"
//===============================================
#if defined(_GUSE_CCV_ON_)
//===============================================
GDECLARE_MAP(GCcv, GCHAR_PTR, GVOID_PTR)
GDEFINE_MAP(GCcv, GCHAR_PTR, GVOID_PTR)
//===============================================
static GCcvO* m_GCcvO = 0;
//===============================================
static void GCcv_Test(int argc, char** argv);
static void GCcv_CreateMatrix(char* matrixId);
//===============================================
GCcvO* GCcv_New() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GCcvO* lObj = (GCcvO*)malloc(sizeof(GCcvO));
    
    lObj->m_matrixMap = GMap_New(GCcv, GCHAR_PTR, GVOID_PTR)();

	lObj->Delete = GCcv_Delete;
	lObj->Test = GCcv_Test;
	lObj->CreateMatrix = GCcv_CreateMatrix;
	return lObj;
}
//===============================================
void GCcv_Delete() {
	GDebug()->Write(__FUNCTION__, _EOA_);
	GCcvO* lObj = GCcv();
	free(lObj);
	m_GCcvO = 0;
}
//===============================================
GCcvO* GCcv() {
	if(m_GCcvO == 0) {
		m_GCcvO = GCcv_New();
	}
	return m_GCcvO;
}
//===============================================
static void GCcv_Test(int argc, char** argv) {
	GDebug()->Write(__FUNCTION__, _EOA_);
}
//===============================================
static void GCcv_CreateMatrix(char* matrixId) {
	GDebug()->Write(__FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lMatrixMap = m_GCcvO->m_matrixMap;
    ccv_dense_matrix_t* lMatrix = ccv_dense_matrix_new(20, 14, CCV_32F | CCV_C1, 0, 0);
    if(lMatrix == 0) {printf("[GCcv] : ERREUR : creation matrice\n"); exit(0);}
    lMatrixMap->SetData(lMatrixMap, matrixId, lMatrix, GMap_EqualChar);
}
//===============================================
#endif
//===============================================
