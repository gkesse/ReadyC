//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
int main(int argc, char** argv) {
	GDebug()->Sep();
	GProcess()->Run(argc, argv);
	return 0;
}
//===============================================
