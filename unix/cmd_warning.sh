#================================================
GPWD=$PWD
GSOAP=$GPWD/data/soap/
#================================================
# GSoap2
#================================================
cd $GSOAP
./cmd_build.sh
#================================================
# GProject
#================================================
cd $GPWD
./cmd_clean.sh
./cmd_compile.sh |& grep "warning"
