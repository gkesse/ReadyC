//===============================================
#include "GTestThreadUnix.h"
#include "GDebug.h"
//===============================================
#if defined(__unix)
//===============================================
static GTestThreadUnixO* m_GTestThreadUnixO = 0;
//===============================================
static void GTestThreadUnix_Run(int argc, char** argv);
static void GTestThreadUnix_Default(int argc, char** argv);
static void GTestThreadUnix_Create(int argc, char** argv);
static void GTestThreadUnix_Arg(int argc, char** argv);
static void GTestThreadUnix_Struct(int argc, char** argv);
static void GTestThreadUnix_SharedMemory(int argc, char** argv);
static void GTestThreadUnix_Exit(int argc, char** argv);
static void GTestThreadUnix_Exit2(int argc, char** argv);
static void GTestThreadUnix_Error(int argc, char** argv);
static void GTestThreadUnix_Join(int argc, char** argv);
static void GTestThreadUnix_Detach(int argc, char** argv);
static void GTestThreadUnix_Attr(int argc, char** argv);
static void GTestThreadUnix_Mutex(int argc, char** argv);
static void GTestThreadUnix_Continue(int argc, char** argv);
static void GTestThreadUnix_Getchar(int argc, char** argv);
static void GTestThreadUnix_Getch(int argc, char** argv);
static void GTestThreadUnix_Getche(int argc, char** argv);
static void GTestThreadUnix_Kbhit(int argc, char** argv);
static void GTestThreadUnix_Arithmetic(int argc, char** argv);
static void GTestThreadUnix_Table(int argc, char** argv);
static void GTestThreadUnix_Clock(int argc, char** argv);
//===============================================
static void* GTestThreadUnix_OnCreate(void* params);
static void* GTestThreadUnix_OnArg(void* params);
static void* GTestThreadUnix_OnStruct(void* params);
static void* GTestThreadUnix_OnSharedMemory(void* params);
static void* GTestThreadUnix_OnExit(void* params);
static void* GTestThreadUnix_OnExit2(void* params);
static void* GTestThreadUnix_OnError(void* params);
static void* GTestThreadUnix_OnJoin(void* params);
static void* GTestThreadUnix_OnDetach(void* params);
static void* GTestThreadUnix_OnAttr(void* params);
static void* GTestThreadUnix_OnMutex(void* params);
//===============================================
GTestThreadUnixO* GTestThreadUnix_New() {
    GTestThreadUnixO* lObj = (GTestThreadUnixO*)malloc(sizeof(GTestThreadUnixO));
    lObj->Delete = GTestThreadUnix_Delete;
    lObj->Run = GTestThreadUnix_Run;
    return lObj;
}
//===============================================
void GTestThreadUnix_Delete() {
    GTestThreadUnixO* lObj = GTestThreadUnix();
    free(lObj);
    m_GTestThreadUnixO = 0;
}
//===============================================
GTestThreadUnixO* GTestThreadUnix() {
    if(m_GTestThreadUnixO == 0) {
        m_GTestThreadUnixO = GTestThreadUnix_New();
    }
    return m_GTestThreadUnixO;
}
//===============================================
static void GTestThreadUnix_Run(int argc, char** argv) {
    for(int i = 3; i < argc;) {
        char* lKey = argv[i++];
        if(!strcmp(lKey, "create")) {GTestThreadUnix_Create(argc, argv); return;}
        if(!strcmp(lKey, "arg")) {GTestThreadUnix_Arg(argc, argv); return;}
        if(!strcmp(lKey, "struct")) {GTestThreadUnix_Struct(argc, argv); return;}
        if(!strcmp(lKey, "memo")) {GTestThreadUnix_SharedMemory(argc, argv); return;}
        if(!strcmp(lKey, "exit")) {GTestThreadUnix_Exit(argc, argv); return;}
        if(!strcmp(lKey, "exit2")) {GTestThreadUnix_Exit2(argc, argv); return;}
        if(!strcmp(lKey, "error")) {GTestThreadUnix_Error(argc, argv); return;}
        if(!strcmp(lKey, "join")) {GTestThreadUnix_Join(argc, argv); return;}
        if(!strcmp(lKey, "detach")) {GTestThreadUnix_Detach(argc, argv); return;}
        if(!strcmp(lKey, "attr")) {GTestThreadUnix_Attr(argc, argv); return;}
        if(!strcmp(lKey, "mutex")) {GTestThreadUnix_Mutex(argc, argv); return;}
        if(!strcmp(lKey, "continue")) {GTestThreadUnix_Continue(argc, argv); return;}
        if(!strcmp(lKey, "getchar")) {GTestThreadUnix_Getchar(argc, argv); return;}
        if(!strcmp(lKey, "getch")) {GTestThreadUnix_Getch(argc, argv); return;}
        if(!strcmp(lKey, "getche")) {GTestThreadUnix_Getche(argc, argv); return;}
        if(!strcmp(lKey, "kbhit")) {GTestThreadUnix_Kbhit(argc, argv); return;}
        if(!strcmp(lKey, "arithmetic")) {GTestThreadUnix_Arithmetic(argc, argv); return;}
        if(!strcmp(lKey, "table")) {GTestThreadUnix_Table(argc, argv); return;}
        if(!strcmp(lKey, "clock")) {GTestThreadUnix_Clock(argc, argv); return;}
        break;
    }
    GTestThreadUnix_Default(argc, argv);
}
//===============================================
static void GTestThreadUnix_Default(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
}
//===============================================
static void GTestThreadUnix_Create(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread;
    pthread_create(&lThread, 0, GTestThreadUnix_OnCreate, 0);
    while(1) {
        GDebug()->Write(2, 3, "Thread principal", _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnCreate(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire", _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Arg(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnArg, (void*)"THREAD_1");
    pthread_create(&lThread2, 0, GTestThreadUnix_OnArg, (void*)"THREAD_2");
    while(1) {
        GDebug()->Write(2, 3, "Thread principal", _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnArg(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    char* lArg = (char*)params;
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire : ", 3, lArg, _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Struct(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnStruct, &(sGTuple2){1, "THREAD_1"});
    pthread_create(&lThread2, 0, GTestThreadUnix_OnStruct, &(sGTuple2){2, "THREAD_2"});
    while(1) {
        GDebug()->Write(2, 3, "Thread principal", _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnStruct(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple2* lParams = (sGTuple2*)params;
    int lId = (int)lParams->item1;
    char* lName = (char*)lParams->item2;
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire : ", 1, lId, 3, " : ", 3, lName, _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_SharedMemory(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2;
    int lCount = 0;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnSharedMemory, &(sGTuple2){"THREAD_1", &lCount});
    pthread_create(&lThread2, 0, GTestThreadUnix_OnSharedMemory, &(sGTuple2){"THREAD_2", &lCount});
    while(1) {
        GDebug()->Write(2, 3, "Thread principal : ", 1, lCount, _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnSharedMemory(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple2* lParams = (sGTuple2*)params;
    char* lName = (char*)lParams->item1;
    int* lCount = (int*)lParams->item2;
    while(1) {
        *lCount += 1;
        GDebug()->Write(2, 3, "Thread secondaire : ", 3, lName, 3, " : ", 1, *lCount, _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Exit(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2, lThread3;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnExit, &(sGTuple1){"THREAD_1"});
    pthread_create(&lThread2, 0, GTestThreadUnix_OnExit, &(sGTuple1){"THREAD_2"});
    pthread_create(&lThread3, 0, GTestThreadUnix_OnExit, &(sGTuple1){"THREAD_3"});
    while(1) {
        GDebug()->Write(2, 3, "Thread principal", _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnExit(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple1* lParams = (sGTuple1*)params;
    char* lName = (char*)lParams->item1;
    int lCount = 0;
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire : ", 3, lName, 3, " : ", 1, lCount, _EOA_);
        if(!strcmp(lName, "THREAD_1") && lCount == 1) pthread_exit(0);
        if(!strcmp(lName, "THREAD_2") && lCount == 3) return 0;
        lCount++;
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Exit2(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2, lThread3;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnExit2, &(sGTuple2){"THREAD_1", 1});
    pthread_create(&lThread2, 0, GTestThreadUnix_OnExit2, &(sGTuple2){"THREAD_2", 2});
    pthread_create(&lThread3, 0, GTestThreadUnix_OnExit2, &(sGTuple2){"THREAD_3", 3});
    GDebug()->Write(2, 3, "Thread principal", _EOA_);
    pthread_exit(0);
}
//===============================================
static void* GTestThreadUnix_OnExit2(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple2* lParams = (sGTuple2*)params;
    char* lName = (char*)lParams->item1;
    int lId = (int)lParams->item2;
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire : ", 3, lName, 3, " : ", 1, lId, _EOA_);
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Error(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread1, lThread2, lThread3;
    pthread_create(&lThread1, 0, GTestThreadUnix_OnError, &(sGTuple1){"THREAD_1"});
    pthread_create(&lThread2, 0, GTestThreadUnix_OnError, &(sGTuple1){"THREAD_2"});
    pthread_create(&lThread3, 0, GTestThreadUnix_OnError, &(sGTuple1){"THREAD_3"});
    while(1) {
        GDebug()->Write(2, 3, "Thread principal", _EOA_);
        sleep(1);
    }
}
//===============================================
static void* GTestThreadUnix_OnError(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple1* lParams = (sGTuple1*)params;
    char* lName = (char*)lParams->item1;
    int lCount = 0;
    while(1) {
        GDebug()->Write(2, 3, "Thread secondaire : ", 3, lName, 3, " : ", 1, lCount, _EOA_);
        if(!strcmp(lName, "THREAD_1") && lCount == 5) {
            char* lPtr = 0;
            lPtr[0] = 0;
        }
        lCount++;
        sleep(1);
    }
    return 0;
}
//===============================================
static void GTestThreadUnix_Join(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    double lMultiply = 1.0;
    double lVal1, lVal2, lVal3;
    void* lResult;
    pthread_t lThread1, lThread2, lThread3;
    lVal1 = 2.0; pthread_create(&lThread1, 0, GTestThreadUnix_OnJoin, &(sGTuple2){&lVal1, &lMultiply});
    lVal2 = 3.0; pthread_create(&lThread2, 0, GTestThreadUnix_OnJoin, &(sGTuple2){&lVal2, &lMultiply});
    lVal3 = 4.0; pthread_create(&lThread3, 0, GTestThreadUnix_OnJoin, &(sGTuple2){&lVal3, &lMultiply});
    pthread_join(lThread1, &lResult);
    pthread_join(lThread2, &lResult);
    pthread_join(lThread3, &lResult);
    GDebug()->Write(2, 3, "Multiply : ", 2, *(double*)lResult, _EOA_);
}
//===============================================
static void* GTestThreadUnix_OnJoin(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple2* lParams = (sGTuple2*)params;
    double* lValue = (double*)lParams->item1;
    double* lMultiply = (double*)lParams->item2;
    (*lMultiply) *= (*lValue);
    GDebug()->Write(2, 2, *lValue, 3, " -> ", 2, *lMultiply, _EOA_);
    return lMultiply;
}
//===============================================
static void GTestThreadUnix_Detach(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread;
    int lCount = 0;
    while(1) {
        int lRes = pthread_create(&lThread, 0, GTestThreadUnix_OnDetach, 0);
        if(lRes != 0) break;
        pthread_detach(lThread);
        lCount++;
        if(lCount % 100 == 0) {
            GDebug()->Write(2, 3, "Thread id : ", 1, lCount, _EOA_);
        }
        usleep(10000);
    }
}
//===============================================
static void* GTestThreadUnix_OnDetach(void* params) {
    GDebug()->Write(0, 3, __FUNCTION__, 3, "()", _EOA_);
    return 0;
}
//===============================================
static void GTestThreadUnix_Attr(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    pthread_t lThread;
    pthread_attr_t lAttr;
    int lCount = 0;
    
    pthread_attr_init(&lAttr);
	pthread_attr_setdetachstate(&lAttr, PTHREAD_CREATE_DETACHED);
    
    while(1) {
        int lRes = pthread_create(&lThread, &lAttr, GTestThreadUnix_OnDetach, 0);
        if(lRes != 0) break;
        lCount++;
        if(lCount % 100 == 0) {
            GDebug()->Write(2, 3, "Thread id : ", 1, lCount, _EOA_);
        }
        usleep(10000);
    }
    pthread_attr_destroy(&lAttr);
}
//===============================================
static void* GTestThreadUnix_OnAttr(void* params) {
    GDebug()->Write(0, 3, __FUNCTION__, 3, "()", _EOA_);
    return 0;
}
//===============================================
static void GTestThreadUnix_Mutex(int argc, char** argv) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_); 
    pthread_mutex_t	lMutex = PTHREAD_MUTEX_INITIALIZER;
    pthread_t lThread;
    int lCount = 0;

    for(int i = 0; i < 5; i++) {
        pthread_create(&lThread, 0, GTestThreadUnix_OnMutex, &(sGTuple3){i, &lCount, &lMutex});
    }
    while(1) {
        sleep(5);
        break;
    }
}
//===============================================
static void* GTestThreadUnix_OnMutex(void* params) {
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    sGTuple3* lParams = (sGTuple3*)params;
    int lId = (int)lParams->item1;
    int* lCount = (int*)lParams->item2;
    pthread_mutex_t* lMutex = (pthread_mutex_t*)lParams->item3;
    pthread_mutex_lock(lMutex);
    *lCount += 1;
    GDebug()->Write(2, 3, "Thread : ", 1, lId, 3, " : ", 1, *lCount, _EOA_);
    pthread_mutex_unlock(lMutex);
    return 0;
}
//===============================================
static void GTestThreadUnix_Continue(int argc, char** argv) {
    for(int i = 0; i < 10; i++) {
        if(i%2 == 0) continue;
        printf("Je compte : %d\n", i);
    }
}
//===============================================
static void GTestThreadUnix_Getchar(int argc, char** argv) {
    printf("Saisir un caractere ? ");
    char lChar = getchar();
    printf("lChar : %c\n", lChar);
}
//===============================================
static void GTestThreadUnix_Getch(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getch();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestThreadUnix_Getche(int argc, char** argv) {
#if defined(__WIN32)
    printf("Saisir un caractere ? ");
    char lChar = getche();
    printf("\nlChar : %c\n", lChar);
#endif
}
//===============================================
static void GTestThreadUnix_Kbhit(int argc, char** argv) {
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
static void GTestThreadUnix_Arithmetic(int argc, char** argv) {
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
static void GTestThreadUnix_Table(int argc, char** argv) {
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
static void GTestThreadUnix_Clock(int argc, char** argv) {
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
