//===============================================
#include <stdio.h>
#include <stdlib.h>
//===============================================
void hello(int lang) {
	if(lang == 0) {
		printf("[ FRENCH ] Bonjour tout le monde\n");
	}
	else if(lang == 1) {
		printf("[ SPANISH ] Hola todo el mundo\n");
	}
}
//===============================================
int main(int argc, char** argv) {
	if(argc <= 1) {
		printf("[ ERROR ] La langue n'est pas definie\n");
		exit(0);
	}
	int lLang = atoi(argv[1]);
	hello(lLang);
	return 0;
}
//===============================================
