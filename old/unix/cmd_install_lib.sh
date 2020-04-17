GLONG_BIT=$(getconf LONG_BIT)
GLIB_ARCH=unix
if [ "$GLONG_BIT" = "64" ] ; then
    GLIB_ARCH=unix64
fi

GLIB_ROOT=/opt/lib
GLIB_BUILD=$GLIB_ROOT/build
GLIB_DEV=$GLIB_ROOT/dev

function GLib_Create() {
    echo "[ INFO ] creation des repertoire lib...[ lib + build + dev ]"
    mkdir -p $GLIB_BUILD
    mkdir -p $GLIB_DEV
}

GLIB_ITEM_NAME="argtable"
GLIB_ITEM_NAME_VERSION="argtable3"
GLIB_ITEM_BUILD=$GLIB_BUILD/$GLIB_ITEM_NAME
GLIB_ITEM_DEV=$GLIB_DEV/$GLIB_ITEM_NAME
GLIB_ITEM_BUILD_SRC=$GLIB_ITEM_BUILD/source
GLIB_ITEM_BUILD_SRC_VERSION=$GLIB_ITEM_BUILD_SRC/$GLIB_ITEM_NAME_VERSION
GLIB_ITEM_BUILD_DIR=$GLIB_ITEM_BUILD/build
GLIB_ITEM_BUILD_PREFIX=$GLIB_ITEM_BUILD/install
GLIB_ITEM_DEV_DIR=$GLIB_ITEM_DEV/$GLIB_ARCH
GLIB_ITEM_LINK="https://github.com/argtable/argtable3.git"
GLIB_ITEM_LINK_DOWNLOAD="git clone $GLIB_ITEM_LINK"
GLIB_ITEM_BUILD_RUN="
cmake -G \"Unix Makefiles\" \
-DCMAKE_INSTALL_PREFIX=$GLIB_ITEM_BUILD_PREFIX \
$GLIB_ITEM_BUILD_SRC_VERSION
"
GLIB_ITEM_BUILD_MAKE="
make
make install
"
GLIB_ITEM_DEV_INSTALL="
cp -rf $GLIB_ITEM_BUILD_PREFIX/include ../include
cp -rf $GLIB_ITEM_BUILD_PREFIX/lib64 ./lib
"

function GLib_Download() {
    echo "[ INFO ] telechargement de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_BUILD_SRC
    cd $GLIB_ITEM_BUILD_SRC
    pwd 
    eval "$GLIB_ITEM_LINK_DOWNLOAD"
}

function GLib_Build() {
    echo "[ INFO ] generation de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_BUILD_DIR
    cd $GLIB_ITEM_BUILD_DIR
    pwd
    eval "$GLIB_ITEM_BUILD_RUN"
}

function GLib_Make() {
    echo "[ INFO ] construction de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_BUILD_DIR
    cd $GLIB_ITEM_BUILD_DIR
    pwd
    eval "$GLIB_ITEM_BUILD_MAKE"
}

function GLib_Install() {
    echo "[ INFO ] installation de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_DEV_DIR
    cd $GLIB_ITEM_DEV_DIR
    pwd
    eval "$GLIB_ITEM_DEV_INSTALL"
}

function GLib_Clean() {
    echo "[ INFO ] suppression du repertoire build de la librairie...[ $GLIB_ITEM_NAME ]"
    #rm -rf $GLIB_ITEM_BUILD_SRC
    #rm -rf $GLIB_ITEM_BUILD_DIR
    #rm -rf $GLIB_ITEM_BUILD_PREFIX
    #rm -rf $GLIB_ITEM_DEV_DIR
    rm -rf $GLIB_BUILD
}

function GLIB_Generate() {
    GLib_Create
    GLib_Download
    GLib_Build
    GLib_Make
    GLib_Install
    GLib_Clean
}

GLIB_Generate
