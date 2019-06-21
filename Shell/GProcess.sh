#!/bin/bash
#================================================
source ./GProcessConfig.sh
source ./GConfig.sh
#================================================
function GProcess_Run() {
    GConfig_GetData PROCESS
    echo ${GConfig_GetData_RET}
    GConfig_ShowData
}
#================================================
