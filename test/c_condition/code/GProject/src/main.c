//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//===============================================
void GElevator_MENU(int argc, char** argv);
void GElevator_CHOICE(int argc, char** argv);
void GElevator_OPEN(int argc, char** argv);
void GElevator_CLOSE(int argc, char** argv);
void GElevator_LEVEL(int argc, char** argv);
void GElevator_START(int argc, char** argv);
void GElevator_QUIT(int argc, char** argv);
//===============================================
char* G_STATE = "S_MENU";
//===============================================
int main(int argc, char** argv) {
    while(1) {
        if(!strcmp(G_STATE, "S_MENU")) {GElevator_MENU(argc, argv);}
        else if(!strcmp(G_STATE, "S_CHOICE")) {GElevator_CHOICE(argc, argv);}
        else if(!strcmp(G_STATE, "S_OPEN")) {GElevator_OPEN(argc, argv);}
        else if(!strcmp(G_STATE, "S_CLOSE")) {GElevator_CLOSE(argc, argv);}
        else if(!strcmp(G_STATE, "S_LEVEL")) {GElevator_LEVEL(argc, argv);}
        else if(!strcmp(G_STATE, "S_START")) {GElevator_START(argc, argv);}
        else if(!strcmp(G_STATE, "S_QUIT")) {GElevator_QUIT(argc, argv);}
        else {break;}
    }
    
    return 0;
}
//===============================================
void GElevator_MENU(int argc, char** argv) {
    printf("\n");
    printf("MENU !!!\n");
    printf("\t%-2s : %s\n", "m", "afficher le menu");
    printf("\t%-2s : %s\n", "1", "ouvrir l'ascenseur");
    printf("\t%-2s : %s\n", "2", "fermer l'ascenseur");
    printf("\t%-2s : %s\n", "3", "choisir un niveau");
    printf("\t%-2s : %s\n", "4", "demarrer l'ascenseur");
    printf("\t%-2s : %s\n", "q", "quitter l'application");
    G_STATE = "S_CHOICE";
}
//===============================================
void GElevator_CHOICE(int argc, char** argv) {
    printf("\n");
    printf("CHOIX ? : ");
    char lAnswer[256];
    gets(lAnswer);
    exit(0);
    if(!strcmp(lAnswer, "m")) {G_STATE = "S_MENU";}
    else if(!strcmp(lAnswer, "1")) {G_STATE = "S_OPEN";}
    else if(!strcmp(lAnswer, "2")) {G_STATE = "S_CLOSE";}
    else if(!strcmp(lAnswer, "3")) {G_STATE = "S_LEVEL";}
    else if(!strcmp(lAnswer, "4")) {G_STATE = "S_START";}
    else if(!strcmp(lAnswer, "q")) {G_STATE = "S_QUIT";}
}
//===============================================
void GElevator_OPEN(int argc, char** argv) {
    printf("[info] ouverture de l'ascenseur...\n");
    G_STATE = "S_CHOICE";
}
//===============================================
void GElevator_CLOSE(int argc, char** argv) {
    printf("[info] fermeture de l'ascenseur...\n");
    G_STATE = "S_CHOICE";
}
//===============================================
void GElevator_LEVEL(int argc, char** argv) {
    printf("[info] choix du niveau de destination...\n");
    G_STATE = "S_CHOICE";
}
//===============================================
void GElevator_START(int argc, char** argv) {
    printf("[info] demarrage de l'ascenseur...\n");
    G_STATE = "S_CHOICE";
}
//===============================================
void GElevator_QUIT(int argc, char** argv) {
    printf("[info] quitter l'application...\n");
    G_STATE = "S_END";
}
//===============================================