//===============================================
<<<<<<< HEAD
#include <stdio.h>
//===============================================
int main(int argc, char** argv) {
	printf("ooooooooooo\n");
	return 0;
=======
#include "GSetting.h"
#include "GOptions.h"
#include "GProcess.h"
#include "GLog.h"
//===============================================
int main(int argc, char** argv) {
    GSetting()->Load("data/config/config.txt");
    GOptions()->GetArgs(argc, argv);
    GProcess()->Run(argc, argv);
    return 0;
>>>>>>> a79590709bb8d64bbaf513dc5d28a44edce361af
}
//===============================================
