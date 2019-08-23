GLIB_ROOT=/opt/lib
GLIB_BUILD=$GLIB_ROOT/build
GLIB_DEV=$GLIB_ROOT/dev

function GLib_Create() {
    echo "[ INFO ] creation du repertoire...[ build ]"
    mkdir -p $GLIB_BUILD
    echo "[ INFO ] creation du repertoire...[ dev ]"
    mkdir -p $GLIB_DEV
}

GLIB_ITEM_NAME="argtable"
GLIB_ITEM_NAME_VERSION="argtable3"
GLIB_ITEM_SRC=$GLIB_BUILD/$GLIB_ITEM_NAME/source
GLIB_ITEM_SRC_VERSION=$GLIB_ITEM_SRC/$GLIB_ITEM_NAME_VERSION
GLIB_ITEM_BUILD=$GLIB_BUILD/$GLIB_ITEM_NAME/build
GLIB_ITEM_LINK=https://github.com/argtable/argtable3.git
GLIB_ITEM_DOWNLOAD="git clone $GLIB_ITEM_LINK"
GLIB_ITEM_BUILD_RUN=`
cd $GLIB_ITEM_BUILD ; \
cmake \
-G "Unix Makefiles" \
$GLIB_ITEM_SRC_VERSION
`

function GLib_Download() {
    echo "[ INFO ] creation du repertoire source de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_SRC
    echo "[ INFO ] deplacement dans le repertoire source de la librairie...[ $GLIB_ITEM_NAME ]"
    cd $GLIB_ITEM_SRC
    echo "[ INFO ] telechargement de la librairie...[ $GLIB_ITEM_NAME ]"
    echo "$GLIB_ITEM_DOWNLOAD"
    $GLIB_ITEM_DOWNLOAD
}

function GLib_Build() {
    echo "[ INFO ] creation du repertoire build de la librairie...[ $GLIB_ITEM_NAME ]"
    mkdir -p $GLIB_ITEM_BUILD
    echo "[ INFO ] deplacement dans le repertoire build de la librairie...[ $GLIB_ITEM_NAME ]"
    cd $GLIB_ITEM_BUILD
    echo "[ INFO ] construction de la librairie...[ $GLIB_ITEM_NAME ]"
    echo "$GLIB_ITEM_BUILD_RUN"
    $GLIB_ITEM_BUILD_RUN
}

function GLib_Clean() {
    echo "[ INFO ] suppression du repertoire build de la librairie...[ $GLIB_ITEM_NAME ]"
    rm -rf $GLIB_ITEM_BUILD
}

#GLib_Clean
#GLib_Create
#GLib_Download
GLib_Build

