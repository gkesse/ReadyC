//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
int main(int argc, char** argv) {
<<<<<<< HEAD
	GDebug()->Sep();
	GProcess()->Run(argc, argv);
	return 0;
=======
    GDebug()->Sep();
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GProcess()->Run(argc, argv);
    return 0;
>>>>>>> bd9c6b9e67282519751bdf6eeca1c21834218466
}
//===============================================
