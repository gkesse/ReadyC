//===============================================
#include "GSetting.h"
#include "GProcess.h"
#include "GConfig.h"
//===============================================
int main(int argc, char** argv) {
    GSetting()->Load("data/config/config.txt");
    GProcess()->Run(argc, argv);
    GProcess()->Delete();
    return 0;
}
//===============================================
