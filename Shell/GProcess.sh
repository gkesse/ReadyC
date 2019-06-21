#!/bin/bash
#================================================
source ./GProcessPrint.sh
source ./GProcessDatabase.sh
source ./GConfig.sh
#================================================
function GProcess_Run() {
	local lKey=$(GConfig_GetData PROCESS)
	if [ "$lKey" == "PRINT" ]; then GProcessPrint_Run
	elif [ "$lKey" == "DATABASE" ]; then GProcessDatabase_Run
	else GProcessPrint_Run; fi
}
#================================================
