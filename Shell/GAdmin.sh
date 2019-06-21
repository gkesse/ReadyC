#!/bin/bash
#================================================
source ./GProcess.sh
source ./GSetting.sh
#================================================
function GMain() {
	GSetting_Load data/config/config.txt
    GProcess_Run
    GConfig_GetData PROCESS
    echo $GConfig_GetData_RET
}
#================================================
GMain
#================================================
