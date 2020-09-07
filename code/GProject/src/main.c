//===============================================
#include "GProcess.h"
#include "GSQLiteMgr.h"
//===============================================
int main(int argc, char** argv) {
    GSQLiteMgr()->Test(argc, argv);
    GProcess()->Run(argc, argv);
    return 0;
}
//===============================================
