//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
int main(int argc, char** argv) {
    GDebug()->Sep();
    GDebug()->Write(__FUNCTION__, "()", _EOA_);
    GProcess()->Run(argc, argv);
    return 0;
}
//===============================================
