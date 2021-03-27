GSRC = $(GPROJECT_SRC)
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/rdc 

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
	rm -f $(GBUILD)/*.o $(GBIN)/*.exe
#================================================
# c
c_install:
	@pacman -S --needed -y make
	@pacman -S --needed -y gcc
#================================================
# sqlite
sqlite_install:
	@pacman -S --needed -y mingw-w64-i686-sqlite3
sqlite_libs:
	@pkg-config --libs sqlite3
sqlite_flags:
	@pkg-config --cflags sqlite3
sqlite_search:
	pkg-config --list-all | grep -ie "sqlite"
#================================================
# gtk
gtk_install:
	@pacman -S --needed -y mingw-w64-i686-gtk3
gtk_libs:
	@pkg-config --libs gtk+-3.0
gtk_flags:
	@pkg-config --cflags gtk+-3.0
gtk_search:
	pkg-config --list-all | grep -ie "gtk"
#================================================
# git
git_push:
	@cd $(GPROJECT_PATH) && git pull && git add --all && git commit -m "Initial Commit" && git push -u origin master
git_clone:
	@cd $(GPROJECT_ROOT) && git clone $(GGIT_URL) $(GGIT_NAME) 
#================================================
