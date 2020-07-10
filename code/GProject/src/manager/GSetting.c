//===============================================
#include "GSetting.h"
#include "GFile.h"
#include "GString.h"
#include "GConfig.h"
//===============================================
#define GSETTING_LINE (256)
#define GSETTING_KEY (256)
#define GSETTING_VALUE (256)
//===============================================
static GSettingO* m_GSettingO = 0;
//===============================================
static void GSetting_Load(char* file);
//===============================================
GSettingO* GSetting_New() {
    GSettingO* lObj = (GSettingO*)malloc(sizeof(GSettingO));
    lObj->Delete = GSetting_Delete;
    lObj->Load = GSetting_Load;
    return lObj;
}
//===============================================
void GSetting_Delete() {
    GSettingO* lObj = GSetting();
    free(lObj);
    m_GSettingO = 0;
}
//===============================================
GSettingO* GSetting() {
    if(m_GSettingO == 0) {
        m_GSettingO = GSetting_New();
    }
    return m_GSettingO;
}
//===============================================
static void GSetting_Load(char* file) {
	GFile()->Exist(file);
    FILE* lFile = fopen(file, "r");
    char lBuffer[GSETTING_LINE];
    char lKey[GSETTING_KEY];
    char lValue[GSETTING_VALUE];

    while(fgets(lBuffer, sizeof(lBuffer), lFile) != NULL) {
        GString()->Trim(lBuffer, lBuffer);
        if(lBuffer[0] == 0) continue;
        char lFirst = lBuffer[0];
        if(lFirst == '#') continue;
        int lCount = GString()->SplitCount(lBuffer, "=");
        if(lCount != 2) continue;
        GString()->SplitGet(lBuffer, lKey, "=", 0);
        GString()->SplitGet(lBuffer, lValue, "=", 1);
        GString()->Trim(lKey, lKey);
        GString()->Trim(lValue, lValue);
        GConfig()->SetData(lKey, lValue);
    }
    fclose(lFile);
}
//===============================================
