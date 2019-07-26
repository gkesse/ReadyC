//===============================================
#include "GSemaphore.h"
//===============================================
static GSemaphoreO* m_GSemaphoreO = 0;
//===============================================
static int GSemaphore_FromBinary(char* binary);
static void GSemaphore_ToBinary(const int decimal, char* binary);
//===============================================
GSemaphoreO* GSemaphore_New() {
    GSemaphoreO* lObj = (GSemaphoreO*)malloc(sizeof(GSemaphoreO));
    lObj->Delete = GSemaphore_Delete;
    lObj->FromBinary = GSemaphore_FromBinary;
    lObj->ToBinary = GSemaphore_ToBinary;
    return lObj;
}
//===============================================
void GSemaphore_Delete() {
    GSemaphoreO* lObj = GSemaphore();
    if(lObj != 0) {
        free(lObj);
    }
    m_GSemaphoreO = 0;
}
//===============================================
GSemaphoreO* GSemaphore() {
    if(m_GSemaphoreO == 0) {
        m_GSemaphoreO = GSemaphore_New();
    }
    return m_GSemaphoreO;
}
//===============================================
static int GSemaphore_FromBinary(char* binary) {
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
static void GSemaphore_ToBinary(const int decimal, char* binary) {
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
