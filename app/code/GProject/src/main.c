//===============================================
#include "GProcess.h"
#include "GManager.h"
//===============================================
int main(int argc, char** argv) {
    GManager()->Main();
    GProcess()->Run(argc, argv);
    return 0;
}
//===============================================