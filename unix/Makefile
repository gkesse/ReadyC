GRLIB = /home/centos/Programs/ReadyLib/dev
GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/GProject.exe 

GINCS = \
<<<<<<< HEAD
    -I./data/gsoap/src \
    -I$(GSRC)/manager \
    -I$(GRLIB)/sqlite/c/include \
    -I$(GRLIB)/gsoap/c/include \
    -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/uuid -I/usr/include/pixman-1 -I/usr/include/libdrm \
    -I/usr/include/dbus-1.0 -I/usr/lib64/dbus-1.0/include \
    -I/usr/include/mysql \

GLIBS = \
    -L$(GRLIB)/gsoap/c/unix64/lib \
    -L./data/gsoap/bin \
    -L/usr/lib64/mysql \
    -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lglib-2.0 -lfreetype -lm \
    -lsqlite3 -lgsoap -lGSoap2 -ldbus-1 -lmysqlclient -lpthread -lrt -ldl \

=======
    -I$(GSRC)/include \
    -I/usr/include/ccv \

GLIBS = \
    -lccv \
    
>>>>>>> c70f04fa4527d8118859c8020c646a2ef7fa40e2
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c)) \

GCFLAGS = \
<<<<<<< HEAD
    -std=c11 \
    -Wall 
    
all: $(GOBJS)
	@mkdir -p $(GBIN)
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@mkdir -p $(GBUILD)
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@mkdir -p $(GBUILD)
=======
    -std=gnu11 \

all: compile run
 
compile: $(GOBJS)
	@if ! [ -d "$(GBIN)" ] ; then mkdir -p $(GBIN) ; fi
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
>>>>>>> c70f04fa4527d8118859c8020c646a2ef7fa40e2
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
clean:
	rm -f $(GBUILD)/*.o $(GBIN)/*.exe
