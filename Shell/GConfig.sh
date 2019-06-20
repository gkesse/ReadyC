#!/bin/bash
#================================================
declare -A m_dataMap
#================================================
function GConfig_SetData() {
	local lKey=$1
	local lValue=$2
	m_dataMap[$lKey]=$lValue
}
#================================================
function GConfig_GetData() {
	GConfig_GetData_RET=${m_dataMap[$1]}
}
#================================================
function GConfig_ShowData() {
	for key in ${!m_dataMap[@]}; do
		echo $key = ${m_dataMap[$key]}
	done
}
#================================================
