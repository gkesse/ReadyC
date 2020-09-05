//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//===============================================
void GFork_Parent() {
    printf("[info] je suis le processus parent\n");
}
//===============================================
void GFork_Child() {
    printf("[info] je suis le processus parent\n");
}
//===============================================
int main(int argc, char** argv) {
    pid_t lPid = fork();
    if(lPid == 0) GFork_Child();
    else GFork_Parent();
    return 0;
}
//===============================================