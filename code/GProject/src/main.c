//===============================================
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
}
//===============================================
