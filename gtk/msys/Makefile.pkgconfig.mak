all:
	
version:
	pkg-config --version
list:
	pkg-config --list-all
search:
	pkg-config --list-all | grep -ie $(GPKGCONFIG_PACKAGE_SEARCH)
libs:
	pkg-config --libs $(GPKGCONFIG_PACKAGE_LIBS)
flags:
	pkg-config --cflags $(GPKGCONFIG_PACKAGE_CFLAGS)
