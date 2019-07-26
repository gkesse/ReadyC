//===============================================
#include "GMutex2.h"
//===============================================
static GMutex2O* m_GMutex2O = 0;
//===============================================
static int GMutex2_FromBinary(char* binary);
static void GMutex2_ToBinary(const int decimal, char* binary);
//===============================================
GMutex2O* GMutex2_New() {
    GMutex2O* lObj = (GMutex2O*)malloc(sizeof(GMutex2O));
    lObj->Delete = GMutex2_Delete;
    lObj->FromBinary = GMutex2_FromBinary;
    lObj->ToBinary = GMutex2_ToBinary;
    return lObj;
}
//===============================================
void GMutex2_Delete() {
    GMutex2O* lObj = GMutex2();
    if(lObj != 0) {
        free(lObj);
    }
    m_GMutex2O = 0;
}
//===============================================
GMutex2O* GMutex2() {
    if(m_GMutex2O == 0) {
        m_GMutex2O = GMutex2_New();
    }
    return m_GMutex2O;
}
//===============================================
static int GMutex2_FromBinary(char* binary) {
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
static void GMutex2_ToBinary(const int decimal, char* binary) {
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
