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
static void GCcv_LoadImage(char* matrixId, char* filename);
static void GCcv_DetectObject(char* facesId, char* matrixId, char* cascadeId,  char* filename);
//===============================================
GCcvO* GCcv_New() {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
	GCcvO* lObj = (GCcvO*)malloc(sizeof(GCcvO));
    
    lObj->m_matrixMap = GMap_New(GCcv, GCHAR_PTR, GVOID_PTR)();
    lObj->m_cascadeMap = GMap_New(GCcv, GCHAR_PTR, GVOID_PTR)();
    lObj->m_facesMap = GMap_New(GCcv, GCHAR_PTR, GVOID_PTR)();

	lObj->Delete = GCcv_Delete;
	lObj->Test = GCcv_Test;
	lObj->CreateMatrix = GCcv_CreateMatrix;
	return lObj;
}
//===============================================
void GCcv_Delete() {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
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
	GDebug()->Write(2, __FUNCTION__, _EOA_);
}
//===============================================
static void GCcv_CreateMatrix(char* matrixId) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lMatrixMap = m_GCcvO->m_matrixMap;
    ccv_dense_matrix_t* lMatrix = ccv_dense_matrix_new(20, 14, CCV_32F | CCV_C1, 0, 0);
    if(lMatrix == 0) {printf("[GCcv] : ERREUR : creation matrice\n"); exit(0);}
    lMatrixMap->SetData(lMatrixMap, matrixId, lMatrix, GMap_EqualChar);
}
//===============================================
static void GCcv_LoadImage(char* matrixId, char* filename) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lMatrixMap = m_GCcvO->m_matrixMap;
    ccv_dense_matrix_t* lMatrix = 0;
    ccv_read(filename, &lMatrix, CCV_IO_RGB_COLOR | CCV_IO_ANY_FILE);
    if(lMatrix == 0) {printf("[GCcv] : ERREUR : creation matrice\n"); exit(0);}
    lMatrixMap->SetData(lMatrixMap, matrixId, lMatrix, GMap_EqualChar);
}
//===============================================
static void GCcv_LoadCascade(char* cascadeId, char* filename) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lCascadeMap = m_GCcvO->m_cascadeMap;
    ccv_scd_classifier_cascade_t* lCascade = ccv_scd_classifier_cascade_read(filename);
    if(lMatrix == 0) {printf("[GCcv] : ERREUR : creation matrice\n"); exit(0);}
    lCascadeMap->SetData(lCascadeMap, cascadeId, lCascade, GMap_EqualChar);
}
//===============================================
static void GCcv_DetectObject(char* facesId, char* matrixId, char* cascadeId,  char* filename) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lFacesMap = m_GCcvO->m_facesMap;
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lMatrixMap = m_GCcvO->m_matrixMap;
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lCascadeMap = m_GCcvO->m_cascadeMap;
    ccv_dense_matrix_t* lMatrix = lMatrixMap->GetData(lMatrixMap, matrixId, GMap_EqualChar);
    ccv_scd_classifier_cascade_t* lCascade = lCascadeMap->GetData(lCascadeMap, cascadeId, GMap_EqualChar);
    ccv_array_t* lFaces = ccv_scd_detect_objects(lMatrix, &lCascade, 1, ccv_scd_default_params);    if(lMatrix == 0) {printf("[GCcv] : ERREUR : creation matrice\n"); exit(0);}
    lFacesMap->SetData(lFacesMap, facesId, lFaces, GMap_EqualChar);
}
//===============================================
static void GCcv_ShowFaces(char* facesId, char* filename) {
	GDebug()->Write(2, __FUNCTION__, _EOA_);
    GMapO(GCcv, GCHAR_PTR, GVOID_PTR)* lFacesMap = m_GCcvO->m_facesMap;
    ccv_array_t* lFaces = lFacesMap->GetData(lFacesMap, facesId, GMap_EqualChar);
    int iFaces = lFaces->rnum
}
//===============================================
#endif
//===============================================
