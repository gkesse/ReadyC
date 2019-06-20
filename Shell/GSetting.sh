#!/bin/bash
#================================================
source ./GConfig.sh
source ./GFile.sh
#================================================
function GSetting_Load() {
	declare -A lLine
	local lFile=$1
	GFile_Exist $lFile
	while IFS= read -r lLine
	do
		# Vider les espace externes dans la chaine
		local lTrim=$(echo "$lLine" | sed -e 's/^[[:space:]]*//')
		# Continuer si la chaine est vide
		if [ "$lTrim" == "" ]; then continue; fi
		# Continuer si la chaine commence par le caractere #
		if [[ ${lTrim:0:1} == "#" ]]; then continue; fi
		# Decouper la chaine en suivant le signe = (Splitter)
		IFS==
		local lSplit=($lTrim)
		# Splitter puis recuperer la valeur key
		local lKey=$(echo "${lSplit[0]}" | sed -e 's/^[[:space:]]*//')
		# Splitter puis recuperer la valeur value
		local lValue=$(echo "${lSplit[1]}" | sed -e 's/^[[:space:]]*//')
		# Sauvegarder la paire key/value
		GConfig_SetData $lKey $lValue
	done < $lFile
	# Afficher la matrice des configs
	GConfig_ShowData
}
#================================================
