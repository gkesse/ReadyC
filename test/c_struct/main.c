//===============================================
#include <stdio.h>
#include <stdlib.h>
//===============================================
typedef struct _sGUser sGUser;
//===============================================
struct _sGUser {
    char* name;
    char* email;
    char* password;
};
//===============================================
static sGUser* GUser_New(char* name, char* email, char* password);
static void GUser_Show(sGUser* obj);
static void GUser_Delete(sGUser* obj);
//===============================================
static sGUser* GUser_New(char* name, char* email, char* password) {
    sGUser* lObj = (sGUser*)malloc(sizeof(sGUser));
    lObj->name = name;
    lObj->email = email;
    lObj->password = password;
    return lObj;
}
//===============================================
static void GUser_Show(sGUser* obj) {
    printf("\n");
    printf("%-20s : %s\n", "Nom", obj->name);
    printf("%-20s : %s\n", "Email", obj->email);
    printf("%-20s : %s\n", "Mot de passe", obj->password);
    printf("\n");
}
//===============================================
static void GUser_Delete(sGUser* obj) {
    free(obj);
}
//===============================================
int main(int argc, char** argv) {
    sGUser* lUser = GUser_New("Gerard KESSE", "gerard.kesse@readydev.com", "123456");
    GUser_Show(lUser);
    GUser_Delete(lUser);
    return 0;
}
//===============================================