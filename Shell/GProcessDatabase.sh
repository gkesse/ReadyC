#!/bin/bash
#================================================
source ./GDatabaseSQLite.sh
source ./GDatabaseSybase.sh
source ./GConfig.sh
#================================================
function GProcessDatabase_Run() {
	local lKey=$(GConfig_GetData DATABASE)
	if [ "$lKey" == "SQLITE" ]; then GDatabaseSQLite_Open
	elif [ "$lKey" == "SYBASE" ]; then GDatabaseSybase_Open
	else GDatabaseSQLite_Open; fi
}
#================================================
