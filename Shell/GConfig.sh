#!/bin/bash
#================================================
declare -A m_GConfigDataMap
#================================================
function GConfig_SetData() {
	local lKey=$1
	local lValue=$2
	m_GConfigDataMap[$lKey]=$lValue
}
#================================================
function GConfig_GetData() {
    local lKey=$1
	local lValue=${m_GConfigDataMap[PROCESS]}
    GConfig_GetData_RET=$lValue
}
#================================================
function GConfig_ShowData() {
	for lKey in ${!m_GConfigDataMap[@]}
    do
        local lValue=${m_GConfigDataMap[$lKey]}
		echo $lKey = $lValue
	done
    echo
}
#================================================
