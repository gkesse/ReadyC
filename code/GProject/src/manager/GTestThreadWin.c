//===============================================
#include "GTestThreadWin.h"
#include "GDebug.h"
//===============================================
#if defined(__WIN32)
//===============================================
static GTestThreadWinO* m_GTestThreadWinO = 0;
//===============================================
static void GTestThreadWin_Run(int argc, char** argv);
static void GTestThreadWin_Default(int argc, char** argv);
static void GTestThreadWin_List(int argc, char** argv);
static void GTestThreadWin_Kill(int argc, char** argv);
static void GTestThreadWin_Kill2(int argc, char** argv);
static void GTestThreadWin_Raise(int argc, char** argv);
static void GTestThreadWin_Killpg(int argc, char** argv);
static void GTestThreadWin_Signal(int argc, char** argv);
static void GTestThreadWin_Tenary(int argc, char** argv);
static void GTestThreadWin_SwitchCase(int argc, char** argv);
static void GTestThreadWin_For(int argc, char** argv);
static void GTestThreadWin_While(int argc, char** argv);
static void GTestThreadWin_DoWhile(int argc, char** argv);
static void GTestThreadWin_Break(int argc, char** argv);
static void GTestThreadWin_Continue(int argc, char** argv);
static void GTestThreadWin_Getchar(int argc, char** argv);
static void GTestThreadWin_Getch(int argc, char** argv);
static void GTestThreadWin_Getche(int argc, char** argv);
static void GTestThreadWin_Kbhit(int argc, char** argv);
static void GTestThreadWin_Arithmetic(int argc, char** argv);
static void GTestThreadWin_Table(int argc, char** argv);
static void GTestThreadWin_Clock(int argc, char** argv);
//===============================================
static void GTestThreadWin_OnSignal(int signalId);
//===============================================
GTestThreadWinO* GTestThreadWin_New() {
    GTestThreadWinO* lObj = (GTestThreadWinO*)malloc(sizeof(GTestThreadWinO));
    lObj->Delete = GTestThreadWin_Delete;
    lObj->Run = GTestThreadWin_Run;
    return lObj;
}
//===============================================
void GTestThreadWin_Delete() {
    GTestThreadWinO* lObj = GTestThreadWin();
    free(lObj);
    m_GTestThreadWinO = 0;
}
//===============================================
GTestThreadWinO* GTestThreadWin() {
    if(m_GTestThreadWinO == 0) {
        m_GTestThreadWinO = GTestThreadWin_New();
    }
    return m_GTestThreadWinO;
}
//===============================================
static void GTestThreadWin_Run(int argc, char** argv) {
    for(int i = 3; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "list")) {GTestThreadWin_List(argc, argv); return;}
        if(!strcmp(lKey, "kill")) {GTestThreadWin_Kill(argc, argv); return;}
        if(!strcmp(lKey, "kill2")) {GTestThreadWin_Kill2(argc, argv); return;}
        if(!strcmp(lKey, "raise")) {GTestThreadWin_Raise(argc, argv); return;}
        if(!strcmp(lKey, "killpg")) {GTestThreadWin_Killpg(argc, argv); return;}
        if(!strcmp(lKey, "signal")) {GTestThreadWin_Signal(argc, argv); return;}
        if(!strcmp(lKey, "tenary")) {GTestThreadWin_Tenary(argc, argv); return;}
        if(!strcmp(lKey, "switch_case")) {GTestThreadWin_SwitchCase(argc, argv); return;}
        if(!strcmp(lKey, "for")) {GTestThreadWin_For(argc, argv); return;}
        if(!strcmp(lKey, "while")) {GTestThreadWin_While(argc, argv); return;}
        if(!strcmp(lKey, "do_while")) {GTestThreadWin_DoWhile(argc, argv); return;}
        if(!strcmp(lKey, "break")) {GTestThreadWin_Break(argc, argv); return;}
        if(!strcmp(lKey, "continue")) {GTestThreadWin_Continue(argc, argv); return;}
        if(!strcmp(lKey, "getchar")) {GTestThreadWin_Getchar(argc, argv); return;}
        if(!strcmp(lKey, "getch")) {GTestThreadWin_Getch(argc, argv); return;}
        if(!strcmp(lKey, "getche")) {GTestThreadWin_Getche(argc, argv); return;}
        if(!strcmp(lKey, "kbhit")) {GTestThreadWin_Kbhit(argc, argv); return;}
        if(!strcmp(lKey, "arithmetic")) {GTestThreadWin_Arithmetic(argc, argv); return;}
        if(!strcmp(lKey, "table")) {GTestThreadWin_Table(argc, argv); return;}
        if(!strcmp(lKey, "clock")) {GTestThreadWin_Clock(argc, argv); return;}
        break;
    }
    GTestThreadWin_Default(argc, argv);
}
//===============================================
static void GTestThreadWin_Default(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
}
//===============================================
static void GTestThreadWin_List(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    for(int i = 1; i < NSIG; i++) {
        char* lName = strsignal(i);
        GDebug()->Write(2, 3, "signal[", 10, 2, i, 3, "] : ", 3, lName, _EOA_);        
    }
}
//===============================================
static void GTestThreadWin_Kill(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pid_t lPid = getpid();
    int lSignalId = 30;
    kill(lPid, lSignalId);
}
//===============================================
static void GTestThreadWin_Kill2(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pid_t lPid = getpid();
    char* lCheck = kill(lPid, 0) == 0 ? "VRAI" : "FAUX";
    GDebug()->Write(2, 3, "Check : ", 3, lCheck, _EOA_);    
}
//===============================================
static void GTestThreadWin_Raise(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    raise(30);
}
//===============================================
static void GTestThreadWin_Killpg(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pid_t lPgid = getpgrp();
    int lSignalId = 30;
    killpg(lPgid, lSignalId);
}
//===============================================
static void GTestThreadWin_Signal(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    for(int i = 1; i < NSIG; i++) {
        int lRes = signal(i, GTestThreadWin_OnSignal);
        if(lRes == SIG_ERR) {
            char* lName = strsignal(i);
            int lPid = (int)getpid();
            GDebug()->Write(2, 3, "ERREUR : ", 1, lPid, 3, " : ", 1, i, 3, " : ", 3, lName, _EOA_);
        }
    }
    while(1) pause();
}
//===============================================
static void GTestThreadWin_OnSignal(int signalId) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char* lName = strsignal(signalId);
    int lPid = (int)getpid();
    char* lEnum = sys_siglist[signalId];
    GDebug()->Write(2,1, lPid, 3, " : ", 1, signalId, 3, " : ", 3, lEnum, 3, " : ", 3, lName, _EOA_);
}
//===============================================
static void GTestThreadWin_Tenary(int argc, char** argv) {
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
static void GTestThreadWin_SwitchCase(int argc, char** argv) {
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
static void GTestThreadWin_For(int argc, char** argv) {
    for(int i = 0; i < 10; i++) {
        printf("Je compte : %d\n", i);
    }
}
//===============================================
static void GTestThreadWin_While(int argc, char** argv) {
    int i = 0;
    while(i < 10) {
        printf("Je compte : %d\n", i);
        i++;
    }
}
//===============================================
static void GTestThreadWin_DoWhile(int argc, char** argv) {
    int i = 0;
    do {
        printf("Je compte : %d\n", i);
        i++;
    } while(i < 10);
}
//===============================================
static void GTestThreadWin_Break(int argc, char** argv) {
    int i = 0;
    while(1) {
        printf("Je compte : %d\n", i);
        i++;
        if(i == 10) break;
    }
}
//===============================================
static void GTestThreadWin_Continue(int argc, char** argv) {
    for(int i = 0; i < 10; i++) {
        if(i%2 == 0) continue;
        printf("Je compte : %d\n", i);
    }
}
//===============================================
static void GTestThreadWin_Getchar(int argc, char** argv) {
    printf("Saisir un caractere ? ");
    char lChar = getchar();
    printf("lChar : %c\n", lChar);
}
//===============================================
static void GTestThreadWin_Getch(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getch();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestThreadWin_Getche(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getche();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestThreadWin_Kbhit(int argc, char** argv) {
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
static void GTestThreadWin_Arithmetic(int argc, char** argv) {
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
static void GTestThreadWin_Table(int argc, char** argv) {
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
static void GTestThreadWin_Clock(int argc, char** argv) {
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
#endif
//===============================================
