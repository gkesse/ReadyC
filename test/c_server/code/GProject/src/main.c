//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
//===============================================
typedef struct _sGServer sGServer;
typedef struct _sGClient sGClient;
//===============================================
struct _sGServer {
    int socketS;
    struct sockaddr_in addressS;
    int portS;
    int listenC;
    int socketC;
    struct sockaddr_in addressC;
    socklen_t lengthC;
    char* ipC;
    int portC;
    char bufferS[256];
    char bufferC[256];
};
//===============================================
int main(int argc, char** argv) {
    sGServer* lServer = (sGServer*)malloc(sizeof(sGServer));
    lServer->portS = 8888;
    lServer->listenC = 5;
    lServer->lengthC = sizeof(lServer->addressC);
    sprintf(lServer->bufferS, "%s", "la connexion a reussi...\n");

    lServer->socketS = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&lServer->addressS, 0, sizeof(struct sockaddr));
	lServer->addressS.sin_family = AF_INET;
	lServer->addressS.sin_addr.s_addr = htonl(INADDR_ANY);
	lServer->addressS.sin_port = htons(lServer->portS);
    
	bind(lServer->socketS, (struct sockaddr*)&lServer->addressS, sizeof(lServer->addressS));
    listen(lServer->socketS, lServer->listenC);
    lServer->socketC = accept(lServer->socketS, (struct sockaddr*)&lServer->addressC, &lServer->lengthC);
    lServer->ipC = inet_ntoa(lServer->addressC.sin_addr);
    lServer->portC = htons(lServer->addressC.sin_port);
    send(lServer->socketC, lServer->bufferS, strlen(lServer->bufferS), 0);
    recv(lServer->socketC, lServer->bufferC, 255, 0);
    
    printf("[info] %-20s : %s\n", "lServer->ipC", lServer->ipC);
    printf("[info] %-20s : %d\n", "lServer->portC", lServer->portC);
    printf("[info] %-20s : %s\n", "lServer->bufferC", lServer->bufferC);
    
    close(lServer->socketC);
    close(lServer->socketS);
    
    free(lServer);
    return 0;
}
//===============================================