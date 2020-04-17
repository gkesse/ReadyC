//===============================================
#include "GProcess.h"
//===============================================
int main(int argc, char** argv) {
	GProcess()->Process(argc, argv);
	GProcess()->Delete();
	return 0;
}
//===============================================
