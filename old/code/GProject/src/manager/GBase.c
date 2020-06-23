//===============================================
#include "GBase.h"
//===============================================
static GBaseO* m_GBaseO = 0;
//===============================================
static int GBase_FromBinary(char* binary);
static void GBase_ToBinary(const int decimal, char* binary);
//===============================================
GBaseO* GBase_New() {
    GBaseO* lObj = (GBaseO*)malloc(sizeof(GBaseO));
    lObj->Delete = GBase_Delete;
    lObj->FromBinary = GBase_FromBinary;
    lObj->ToBinary = GBase_ToBinary;
    return lObj;
}
//===============================================
void GBase_Delete() {
    GBaseO* lObj = GBase();
    if(lObj != 0) {
        free(lObj);
    }
    m_GBaseO = 0;
}
//===============================================
GBaseO* GBase() {
    if(m_GBaseO == 0) {
        m_GBaseO = GBase_New();
    }
    return m_GBaseO;
}
//===============================================
static int GBase_FromBinary(char* binary) {
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
static void GBase_ToBinary(const int decimal, char* binary) {
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
