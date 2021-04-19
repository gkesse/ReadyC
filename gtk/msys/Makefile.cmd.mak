GSRC = $(GPROJECT_SRC)
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/rdc.exe

GINCS = \
    -I$(GSRC)/include \
    `pkg-config --cflags gtk+-3.0` \
    `pkg-config --cflags sqlite3` \

GLIBS = \
    `pkg-config --libs gtk+-3.0` \
    `pkg-config --libs sqlite3` \

GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c)) \

GCFLAGS = \
    -std=gnu18 \
    -W -Wall \
    -Wno-unused-parameter \
    -Wno-deprecated-declarations \

#================================================
all: clean_exe compile run

compile: $(GOBJS)
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	$(GTARGET) $(argv)
clean_exe:
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	rm -f $(GBIN)/*
clean:
	@if ! [ -d $(GBIN) ] ; then mkdir -p $(GBIN) ; fi
	@if ! [ -d $(GBUILD) ] ; then mkdir -p $(GBUILD) ; fi
	rm -f $(GBUILD)/* $(GBIN)/*
#================================================
# c
c_install:
	@pacman -S --needed --noconfirm make
	@pacman -S --needed --noconfirm gcc
#================================================
# sqlite
sqlite_install:
	@pacman -S --needed --noconfirm mingw-w64-i686-sqlite3
sqlite_libs:
	@pkg-config --libs sqlite3
sqlite_flags:
	@pkg-config --cflags sqlite3
sqlite_search:
	pkg-config --list-all | grep -ie "sqlite"
#================================================
# gtk
gtk_install:
	@pacman -S --needed --noconfirm mingw-w64-i686-gtk3
gtk_libs:
	@pkg-config --libs gtk+-3.0
gtk_flags:
	@pkg-config --cflags gtk+-3.0
gtk_search:
	pkg-config --list-all | grep -ie "gtk"
#================================================
# opengl
opengl_install:
	@pacman -S --needed --noconfirm mingw-w64-i686-mesa
	@pacman -S --needed --noconfirm mingw-w64-i686-freeglut
	@pacman -S --needed --noconfirm mingw-w64-i686-glew
opengl_search:
	pkg-config --list-all | grep -ie "mesa"
#================================================
# opencv (no work)
opencv_deps:
	@pacman -S --needed --noconfirm zlib-devel
	@pacman -S --needed --noconfirm mingw-w64-i686-libtiff
opencv_clone:
	@if ! [ -d $(GOPENCV_ROOT) ] ; then mkdir -p $(GOPENCV_ROOT) ; fi
	@cd $(GOPENCV_ROOT) && git clone -b 2.4.13.7 https://github.com/opencv/opencv
opencv_cmake:
	@if ! [ -d $(GOPENCV_BUILD) ] ; then mkdir -p $(GOPENCV_BUILD) ; fi
	@cd $(GOPENCV_BUILD) && cmake $(GOPENCV_SRC) \
	-DCMAKE_INSTALL_PREFIX=$(GOPENCV_INSTALL) \
	-G "Unix Makefiles"
opencv_make:
	@cd $(GOPENCV_BUILD) && make
#================================================
# git
git_install:
	@pacman -S --needed --noconfirm git
	@pacman -S --needed --noconfirm vim
git_config:
	@git config --global user.name "Gerard KESSE"
	@git config --global user.email "tiakagerard@hotmail.com"
	@git config --global core.editor "vim"
	@git config --list
git_store:
	@git config credential.helper store
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_push_o:
	@cd $(GPROJECT_PATH) && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
