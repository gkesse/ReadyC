//===============================================
#include "GThread2.h"
//===============================================
static GThread2O* m_GThread2O = 0;
//===============================================
static int GThread2_FromBinary(char* binary);
static void GThread2_ToBinary(const int decimal, char* binary);
//===============================================
GThread2O* GThread2_New() {
    GThread2O* lObj = (GThread2O*)malloc(sizeof(GThread2O));
    lObj->Delete = GThread2_Delete;
    lObj->FromBinary = GThread2_FromBinary;
    lObj->ToBinary = GThread2_ToBinary;
    return lObj;
}
//===============================================
void GThread2_Delete() {
    GThread2O* lObj = GThread2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GThread2O = 0;
}
//===============================================
GThread2O* GThread2() {
    if(m_GThread2O == 0) {
        m_GThread2O = GThread2_New();
    }
    return m_GThread2O;
}
//===============================================
static int GThread2_FromBinary(char* binary) {
	int i = strlen(binary) - 1;
	int lBinary = 0;
	double lPow = 1;
	int lBase = 2;
	while(i >= 0) {
		char lDigit = binary[i];
		int lValue = 0;
		if(lDigit == '1') lValue = 1;
		lBinary += lValue * lPow;
		lPow *= lBase;
		i--;
	}
	return lBinary;
}
//===============================================
static void GThread2_ToBinary(const int decimal, char* binary) {
	char lBinary[16];
	int lBase = 2;
	int lQuotient = decimal;
	int lRemainder = 0;
	int i = 0;
	const char lBinaryMap[] = {'0', '1'};
	while(1) {
		lRemainder = lQuotient % lBase;
		lQuotient = lQuotient / lBase;
		lBinary[i] = lBinaryMap[lRemainder];
		i++;
		if(lQuotient == 0) break;
	}
	lBinary[i] = 0;
	int lSize = strlen(lBinary);
	for(i = 0; i < lSize; i++) {
		int j = lSize - i - 1;
		binary[i] = lBinary[j];
	}
	binary[i] = 0;
}
//===============================================
