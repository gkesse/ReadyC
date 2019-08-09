GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/GProject.exe

GINCS = \
    -I$(GSRC)/manager \
    -I/opt/gSOAP/gsoap \
    -I/home/centos/LOCAL/unix/data/soap/src/ \
    -I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/uuid -I/usr/include/pixman-1 -I/usr/include/libdrm \
    -I/usr/include/dbus-1.0 -I/usr/lib64/dbus-1.0/include \
    -I/usr/include/mysql \

GLIBS = \
    -L/home/centos/LOCAL/unix/data/soap/bin/ \
    -L/usr/lib64/mysql \
    -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lglib-2.0 -lfreetype -lm \
    -lsqlite3 -lGSoap2 -ldbus-1 -lmysqlclient -lpthread -lrt -ldl \

GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c))

CFLAGS = \
    -std=c11 -fno-builtin
    
all: $(GOBJS)
	@mkdir -p $(GBIN)
	gcc $(CFLAGS) -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@mkdir -p $(GBUILD)
	gcc $(CFLAGS) -Wall -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@mkdir -p $(GBUILD)
	gcc $(CFLAGS) -Wall -c $< -o $@ $(GINCS)
clean:
	rm -f $(GBUILD)/*.o $(GBIN)/*.exe
