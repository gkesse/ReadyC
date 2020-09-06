//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//===============================================
void GProcess_Parent();
void GProcess_Child();
//===============================================
int lCount = 0;
//===============================================
void GProcess_Parent() {
    printf("[info] je suis le processus parent\n");
    while(1) {
        lCount += 1;
        printf("[info] le parent compte : %d\n", lCount);
        sleep(5);
    }
}
//===============================================
void GProcess_Child() {
    printf("[info] je suis le processus fils\n");
    while(1) {
        lCount += 1;
        printf("[info] le fils compte : %d\n", lCount);
        sleep(5);
    }
}
//===============================================
int main(int argc, char** argv) {
    int lCount = 0;
    pid_t lPid = fork();
    if(lPid == 0) GProcess_Child();
    else GProcess_Parent();
    return 0;
}
//===============================================