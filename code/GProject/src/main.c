//===============================================
#include "GProcess.h"
#include "GDebug.h"
//===============================================
int main(int argc, char** argv) {
    GDebug()->Sep(2);
    GDebug()->Write(2, 3, __FUNCTION__, 3, "()", _EOA_);
    GProcess()->Run(argc, argv);
    return 0;
}
//===============================================
