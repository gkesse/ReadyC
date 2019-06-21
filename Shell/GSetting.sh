#!/bin/bash
#================================================
source ./GConfig.sh
source ./GFile.sh
#================================================
function GSetting_Load() {
	local lLine
	local lFile=$1
	GFile_Exist $lFile
	while IFS= read -r lLine
	do
		# Vider les espace gauche dans la chaine (Trim Gauche)
		local lTrim=$(echo "${lLine}" | sed -e 's/^[[:space:]]*//')
		# Continuer si la chaine est vide
		if [ "$lTrim" == "" ]; then continue; fi
		# Continuer si la chaine commence par le caractere #
		if [[ ${lTrim:0:1} == "#" ]]; then continue; fi
		# Decouper la chaine en suivant le signe = (Split)
		IFS==
		local lSplit=($lTrim)
		# Splitter recuperer puis trimmer la valeur key
		local lKey=$(echo ${lSplit[0]} | xargs)
		# Splitter puis recuperer la valeur value
		local lValue=$(echo ${lSplit[1]} | xargs)
		# Sauvegarder la paire key/value
		GConfig_SetData $lKey $lValue
	done < $lFile
	# Afficher la matrice des configs
	local lConfigShow=$(GConfig_GetData CONFIG_SHOW)
	if [ "$lConfigShow" == "TRUE" ]; then GConfig_ShowData; fi
}
#================================================
