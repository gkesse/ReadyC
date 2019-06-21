#!/bin/bash
#================================================
source ./GSetting.sh
source ./GProcess.sh
#================================================
function GMain() {
	GSetting_Load data/config/config.txt
    GProcess_Run 
}
#================================================
echo
GMain
echo
#================================================
