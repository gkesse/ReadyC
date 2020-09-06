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
typedef struct _sGClient sGClient;
//===============================================
struct _sGClient {
    int socketC;
    struct sockaddr_in addressS;
    char* ipS;
    int portS;
    char bufferS[255];
    char bufferC[255];
};
//===============================================
int main(int argc, char** argv) {
    sGClient* lClient = (sGClient*)malloc(sizeof(sGClient));
    lClient->ipS = "127.0.0.1";
    lClient->portS = 8888;
    sprintf(lClient->bufferC, "%s", "le message a ete recu...\n");

    lClient->socketC = socket(AF_INET, SOCK_STREAM, 0);
    
    memset(&lClient->addressS, 0, sizeof(struct sockaddr));
	lClient->addressS.sin_family = AF_INET;
	lClient->addressS.sin_addr.s_addr =  inet_addr(lClient->ipS);
	lClient->addressS.sin_port = htons(lClient->portS);
    
	connect(lClient->socketC, (struct sockaddr*)&lClient->addressS, sizeof(lClient->addressS));
    recv(lClient->socketC, lClient->bufferS, 255, 0);
    send(lClient->socketC, lClient->bufferC, strlen(lClient->bufferC), 0);
    
    printf("[info] %-20s : %s\n", "lClient->bufferS", lClient->bufferS);

    shutdown(lClient->socketC);
    
    free(lClient);
    sleep(5);
    return 0;
}
//===============================================