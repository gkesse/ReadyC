#!/bin/bash
#================================================
function GFile_Exist() {
	local lFile=$1
	if [ ! -e $lFile ]
	then
		echo "[ GFile ]  Erreur GFile_Exist: $lFile"
		exit
	fi
}
#================================================
