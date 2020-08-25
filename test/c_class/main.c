//===============================================
#include <stdio.h>
#include <stdlib.h>
//===============================================
typedef struct _sGUser sGUser;
//===============================================
struct _sGUser {
    //===============================================
    void (*Delete)(sGUser* obj);
    void (*Show)(sGUser* obj);
    //===============================================
    char* name;
    char* email;
    char* password;
    //===============================================
};
//===============================================
static void GUser_Create(sGUser* obj, char* name, char* email, char* password);
static sGUser* GUser_New(char* name, char* email, char* password);
static void GUser_Show(sGUser* obj);
static void GUser_Delete(sGUser* obj);
//===============================================
static void GUser_Create(sGUser* obj, char* name, char* email, char* password) {
    //===============================================
    obj->name = name;
    obj->email = email;
    obj->password = password;
    //===============================================
    obj->Delete = GUser_Delete;
    obj->Show = GUser_Show;
    //===============================================
}
//===============================================
static sGUser* GUser_New(char* name, char* email, char* password) {
    sGUser* lObj = (sGUser*)malloc(sizeof(sGUser));
    GUser_Create(lObj, name, email, password);
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
    // forme dynamique
    sGUser* lUser = GUser_New("Gerard KESSE", "gerard.kesse@readydev.com", "123456");
    lUser->Show(lUser);
    lUser->Delete(lUser);
    lUser->Show(lUser);
    // forme statique
    sGUser lUser2;
    GUser_Create(&lUser2, "Jean DUPONT", "jean.dupont@readydev.com", "654321");
    lUser2.Show(&lUser2);
    return 0;
}
//===============================================