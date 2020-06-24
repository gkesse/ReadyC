//===============================================
#include "GTestBasic.h"
//===============================================
static GTestBasicO* m_GTestBasicO = 0;
//===============================================
static void GTestBasic_Run(int argc, char** argv);
static void GTestBasic_Default(int argc, char** argv);
static void GTestBasic_Printf(int argc, char** argv);
static void GTestBasic_PrintfVar(int argc, char** argv);
static void GTestBasic_PrintfFormat(int argc, char** argv);
static void GTestBasic_Scanf(int argc, char** argv);
static void GTestBasic_Fgets(int argc, char** argv);
static void GTestBasic_IfElse(int argc, char** argv);
static void GTestBasic_Tenary(int argc, char** argv);
static void GTestBasic_SwitchCase(int argc, char** argv);
static void GTestBasic_For(int argc, char** argv);
static void GTestBasic_While(int argc, char** argv);
static void GTestBasic_DoWhile(int argc, char** argv);
static void GTestBasic_Break(int argc, char** argv);
static void GTestBasic_Continue(int argc, char** argv);
static void GTestBasic_Getchar(int argc, char** argv);
static void GTestBasic_Getch(int argc, char** argv);
static void GTestBasic_Getche(int argc, char** argv);
static void GTestBasic_Kbhit(int argc, char** argv);
static void GTestBasic_Arithmetic(int argc, char** argv);
static void GTestBasic_Table(int argc, char** argv);
static void GTestBasic_Clock(int argc, char** argv);
//===============================================
GTestBasicO* GTestBasic_New() {
    GTestBasicO* lObj = (GTestBasicO*)malloc(sizeof(GTestBasicO));
    lObj->Delete = GTestBasic_Delete;
    lObj->Run = GTestBasic_Run;
    return lObj;
}
//===============================================
void GTestBasic_Delete() {
    GTestBasicO* lObj = GTestBasic();
    free(lObj);
    m_GTestBasicO = 0;
}
//===============================================
GTestBasicO* GTestBasic() {
    if(m_GTestBasicO == 0) {
        m_GTestBasicO = GTestBasic_New();
    }
    return m_GTestBasicO;
}
//===============================================
static void GTestBasic_Run(int argc, char** argv) {
    for(int i = 3; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "printf")) {GTestBasic_Printf(argc, argv); return;}
        if(!strcmp(lKey, "printf_var")) {GTestBasic_PrintfVar(argc, argv); return;}
        if(!strcmp(lKey, "printf_format")) {GTestBasic_PrintfFormat(argc, argv); return;}
        if(!strcmp(lKey, "scanf")) {GTestBasic_Scanf(argc, argv); return;}
        if(!strcmp(lKey, "fgets")) {GTestBasic_Fgets(argc, argv); return;}
        if(!strcmp(lKey, "if_else")) {GTestBasic_IfElse(argc, argv); return;}
        if(!strcmp(lKey, "tenary")) {GTestBasic_Tenary(argc, argv); return;}
        if(!strcmp(lKey, "switch_case")) {GTestBasic_SwitchCase(argc, argv); return;}
        if(!strcmp(lKey, "for")) {GTestBasic_For(argc, argv); return;}
        if(!strcmp(lKey, "while")) {GTestBasic_While(argc, argv); return;}
        if(!strcmp(lKey, "do_while")) {GTestBasic_DoWhile(argc, argv); return;}
        if(!strcmp(lKey, "break")) {GTestBasic_Break(argc, argv); return;}
        if(!strcmp(lKey, "continue")) {GTestBasic_Continue(argc, argv); return;}
        if(!strcmp(lKey, "getchar")) {GTestBasic_Getchar(argc, argv); return;}
        if(!strcmp(lKey, "getch")) {GTestBasic_Getch(argc, argv); return;}
        if(!strcmp(lKey, "getche")) {GTestBasic_Getche(argc, argv); return;}
        if(!strcmp(lKey, "kbhit")) {GTestBasic_Kbhit(argc, argv); return;}
        if(!strcmp(lKey, "arithmetic")) {GTestBasic_Arithmetic(argc, argv); return;}
        if(!strcmp(lKey, "table")) {GTestBasic_Table(argc, argv); return;}
        if(!strcmp(lKey, "clock")) {GTestBasic_Clock(argc, argv); return;}
        break;
    }
    GTestBasic_Default(argc, argv);
}
//===============================================
static void GTestBasic_Default(int argc, char** argv) {
    printf("%s\n", __FUNCTION__);
}
//===============================================
static void GTestBasic_Printf(int argc, char** argv) {
    printf("Bonjour tout le monde\n");
}
//===============================================
static void GTestBasic_PrintfVar(int argc, char** argv) {
    char* lString = "Bonjour tout le monde";
    int lInt = 1234;
    float lFoat = 3.14;
    printf("lString: %s\n", lString);
    printf("lInt: %d\n", lInt);
    printf("lFoat: %f\n", lFoat);
}
//===============================================
static void GTestBasic_PrintfFormat(int argc, char** argv) {
    char* lString = "Bonjour tout le monde";
    int lInt = 1234;
    float lFoat = 3.14;
    printf("%-20s : %s\n", "lString", lString);
    printf("%-20s : %d\n", "lInt", lInt);
    printf("%-20s : %f\n", "lFoat", lFoat);
}
//===============================================
static void GTestBasic_Scanf(int argc, char** argv) {
    char lString[256];
    int lInt;
    float lFoat;
    printf("Saisir une chaine ? ");
    scanf("%s", lString);
    printf("Saisir un entier ? ");
    scanf("%d", &lInt);
    printf("Saisir un reel ? ");
    scanf("%f", &lFoat);
    printf("\nVous avez saisi :\n");
    printf("%-20s : %s\n", "lString", lString);
    printf("%-20s : %d\n", "lInt", lInt);
    printf("%-20s : %f\n", "lFoat", lFoat);
}
//===============================================
static void GTestBasic_Fgets(int argc, char** argv) {
    char lString[256];
    printf("Saisir une chaine ? ");
    fgets(lString, 255, stdin);
    printf("\nVous avez saisi :\n");
    printf("%-20s : %s\n", "lString", lString);
}
//===============================================
static void GTestBasic_IfElse(int argc, char** argv) {
    int lMin = 4000;
    int lMax = 6000;
    int lVal = 0;
    
    for(int i = 0; i < 10; i++) {
        if(lVal < lMin) {
            printf("L'entier (%4d) est inferieur a (%d)\n", lVal, lMin);
        }
        else if(lVal <= lMax) {
            printf("L'entier (%4d) est compris entre (%d) et (%d)\n", lVal, lMin, lMax);
        }
        else {
            printf("L'entier (%4d) est superieur a (%d)\n", lVal, lMax);
        }
        lVal += 1000;
    }
}
//===============================================
static void GTestBasic_Tenary(int argc, char** argv) {
    char* lVmin = "-5V";
    char* lVmax = "+5V";
    float lVref = 0.5;
    float lVin = 0;
    
    for(int i = 0; i < 10; i++) {
        char* lVt = (lVin >= lVref) ? lVmax : lVmin;
        printf("Vin : %.1f ; Vt : %s\n", lVin, lVt);
        lVin += 0.1;
    }
}
//===============================================
static void GTestBasic_SwitchCase(int argc, char** argv) {
    int lState = 0;
    int lContinue = 1;
    
    while(lContinue) {
        switch(lState) {
            case 0:
                printf("Etat %d : Etat initial\n", lState);
                lState = 1;
                break;
            case 1:
                printf("Etat %d : Feux vert\n", lState);
                lState = 2;
                break;
            case 2:
                printf("Etat %d : Feux orange\n", lState);
                lState = 3;
                break;
            case 3:
                printf("Etat %d : Feux rouge\n", lState);
                lState = 4;
                break;
            default:
                printf("Etat %d : Etat par defaut\n", lState);
                lContinue = 0;
                break;
        }
    }
}
//===============================================
static void GTestBasic_For(int argc, char** argv) {
    for(int i = 0; i < 10; i++) {
        printf("Je compte : %d\n", i);
    }
}
//===============================================
static void GTestBasic_While(int argc, char** argv) {
    int i = 0;
    while(i < 10) {
        printf("Je compte : %d\n", i);
        i++;
    }
}
//===============================================
static void GTestBasic_DoWhile(int argc, char** argv) {
    int i = 0;
    do {
        printf("Je compte : %d\n", i);
        i++;
    } while(i < 10);
}
//===============================================
static void GTestBasic_Break(int argc, char** argv) {
    int i = 0;
    while(1) {
        printf("Je compte : %d\n", i);
        i++;
        if(i == 10) break;
    }
}
//===============================================
static void GTestBasic_Continue(int argc, char** argv) {
    for(int i = 0; i < 10; i++) {
        if(i%2 == 0) continue;
        printf("Je compte : %d\n", i);
    }
}
//===============================================
static void GTestBasic_Getchar(int argc, char** argv) {
    printf("Saisir un caractere ? ");
    char lChar = getchar();
    printf("lChar : %c\n", lChar);
}
//===============================================
static void GTestBasic_Getch(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getch();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestBasic_Getche(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getche();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestBasic_Kbhit(int argc, char** argv) {
#if defined(__WIN32)
    printf("Appuyer q pour quitter ? ");
    while(1) {
        if(kbhit() != 0) {
            char lChar = getch();
            if(lChar == 'q') break;
        }
    }
    printf("\n");
#endif
}
//===============================================
static void GTestBasic_Arithmetic(int argc, char** argv) {
    float lAdd = 22 + 7;
    float lSub = 22 - 7;
    float lMul = 22 * 7;
    float lDiv = (float)22 / 7;
    int lQuotient = 22 / 7;
    int lModulo = 22 % 7;
    printf("%-20s : %f\n", "lAdd", lAdd);
    printf("%-20s : %f\n", "lSub", lSub);
    printf("%-20s : %f\n", "lMul", lMul);
    printf("%-20s : %f\n", "lDiv", lDiv);
    printf("%-20s : %d\n", "lQuotient", lQuotient);
    printf("%-20s : %d\n", "lModulo", lModulo);
}
//===============================================
static void GTestBasic_Table(int argc, char** argv) {
    int lTab[10];
    int lNumber = 5;
    for(int i = 0; i < 10; i++) {
        lTab[i] = lNumber * (i + 1);
    }
    for(int i = 0; i < 10; i++) {
        int lItem = lTab[i];
        printf("%2d x %2d = %2d\n", lNumber, (i + 1), lItem);
    }
}
//===============================================
static void GTestBasic_Clock(int argc, char** argv) {
    ulong lDelay = 1000000000;
    clock_t lStart = clock();
    for(int i = 0; i< lDelay; i++);
    clock_t lEnd = clock();
    clock_t lTicks = lEnd - lStart;
    double lTime = ((double)lTicks * 1000) / CLOCKS_PER_SEC;
    printf("Temps ecoule : %.0f (ms)\n", lTime);
    double lTimeFor = (double)(lTime * 1000 * 1000) / lDelay;
    printf("Temps ecoule (for) : %.2f (ns)\n", lTimeFor);
}
//===============================================
