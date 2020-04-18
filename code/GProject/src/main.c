//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
int main(int argc, char** argv) {
	GDebug()->Sep();
	GProcess()->Process(argc, argv);
	return 0;
}
//===============================================
