//===============================================
#include "GSetting.h"
#include "GOptions.h"
#include "GProcess.h"
//===============================================
int main(int argc, char** argv) {
    GSetting()->Load("data/config/config.txt");
    GOptions()->GetArgs(argc, argv);
    GProcess()->Run(argc, argv);
    GProcess()->Delete();
    return 0;
}
//===============================================
#if 0
//===============================================
#include "GSetting.h"
#include "GOptions.h"
#include "GProcess.h"
//===============================================
int main(int argc, char** argv) {
    GSetting()->Load("data/config/config.txt");
    GOptions()->GetArgs(argc, argv);
    GProcess()->Run(argc, argv);
    GProcess()->Delete();
    return 0;
}
//===============================================
#endif
//===============================================
