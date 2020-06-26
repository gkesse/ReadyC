//===============================================
#include "GProcessRaceCondition.h"
#include "GConsole.h"
#include "GLog.h"
//===============================================
typedef struct _GAccount {
    char* m_name;
    double m_balance;    
} GAccount;
//===============================================
static GProcessO* m_GProcessRaceConditionO = 0;
//===============================================
static void GProcessRaceCondition_Run(int argc, char** argv);
static void GProcessRaceCondition_ShowAccount(GAccount account);
static void GProcessRaceCondition_TransferMoney(GAccount* fromAccount, GAccount* toAccount, double money);
//===============================================
GProcessO* GProcessRaceCondition_New() {
    GProcessO* lParent = GProcess_New();
    GProcessRaceConditionO* lChild = (GProcessRaceConditionO*)malloc(sizeof(GProcessRaceConditionO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessRaceCondition_Delete;
    lParent->Run = GProcessRaceCondition_Run;
    return lParent;
}
//===============================================
void GProcessRaceCondition_Delete() {
	GProcess_Delete(m_GProcessRaceConditionO);
    m_GProcessRaceConditionO = 0;
}
//===============================================
GProcessO* GProcessRaceCondition() {
    if(m_GProcessRaceConditionO == 0) {
        m_GProcessRaceConditionO = GProcessRaceCondition_New();
    }
    return m_GProcessRaceConditionO;
}
//===============================================
static void GProcessRaceCondition_Run(int argc, char** argv) {
    //GLog()->Write("#================================================");
    //GLog()->Write("# Execution de la fonction : GProcessRaceCondition_Run");
    //GLog()->Write("#================================================");
    GConsole()->Print("=================================================\n");
    GConsole()->Print("Je teste une race condition\n");
    GConsole()->Print("=================================================\n");
    GAccount lAccount1 = {"ACCOUNT_1", 100.0};
    GAccount lAccount2 = {"ACCOUNT_2", 100.0};
    GProcessRaceCondition_ShowAccount(lAccount1);
    GProcessRaceCondition_ShowAccount(lAccount2);
    GProcessRaceCondition_TransferMoney(&lAccount1, &lAccount2, 50.0);
    GProcessRaceCondition_ShowAccount(lAccount1);
    GProcessRaceCondition_ShowAccount(lAccount2);
    GConsole()->Print("=================================================\n");
}
//===============================================
static void GProcessRaceCondition_ShowAccount(GAccount account) {
    GConsole()->Print("[ INFO ] J'affiche les details du compte (%s)\n", account.m_name);
    GConsole()->Print("%-10s : %.2f €\n", account.m_name, account.m_balance);
}
//===============================================
static void GProcessRaceCondition_TransferMoney(GAccount* fromAccount, GAccount* toAccount, double money) {
    GConsole()->Print("[ INFO ] Je transferts (%.2f €) du compte (%s) vers le compte (%s)\n", money, fromAccount->m_name, toAccount->m_name);
    if(fromAccount->m_balance < money) {
        GConsole()->Print("[ ERREUR ] le transfert d'argent a echoue\n");
        GConsole()->Print("[ ERREUR ] le montant du transfert (%.2f €) est superieur au montant disponible sur le compte (%s) (%.2f €)\n", money, fromAccount->m_name, fromAccount->m_balance);
        return;  
    }
    fromAccount->m_balance -= money;
    toAccount->m_balance += money;
    GConsole()->Print("[ INFO ] le transfert d'argent a reussi\n");
}
//===============================================
