GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/GProject.exe


GTK_LIBS = \

GINCS = \
<<<<<<< HEAD
    -I$(GSRC)/manager \
    -I/opt/gSOAP/gsoap \
    -I/home/centos/Programs/ReadyC/unix/data/soap/src \


GLIBS = \
    -L/home/centos/Programs/ReadyC/unix/data/soap/bin \
    -lGSoap -lsqlite3 \
            
=======
	-I/usr/include/gtk-2.0 -I/usr/lib64/gtk-2.0/include -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/glib-2.0 -I/usr/lib64/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/libpng15 -I/usr/include/uuid -I/usr/include/pixman-1 -I/usr/include/libdrm \
	-I/home/centos/LOCAL/unix/data/soap/src \
	-I/opt/gSOAP/gsoap \
	-I$(GSRC)/manager \

GLIBS = \
	-L/home/centos/LOCAL/unix/data/soap/bin \
	-lpthread -lm -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgio-2.0 -lpangoft2-1.0 -lpangocairo-1.0 -lgdk_pixbuf-2.0 -lcairo -lpango-1.0 -lfontconfig -lgobject-2.0 -lglib-2.0 -lfreetype \
	-lsqlite3 -lGSoap2 \
	
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c))
    
GCFLAGS = \
	-std=c11 -c -fmessage-length=0
	
all: $(GOBJS)
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS)
$(GBUILD)/%.o: $(GSRC)/%.c
<<<<<<< HEAD
	gcc -std=c11 -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	gcc -std=c11 -c $< -o $@ $(GINCS)
=======
	gcc $(GCFLAGS) $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	gcc $(GCFLAGS) $< -o $@ $(GINCS)
>>>>>>> e856714f5bde9182b2f094384f4252baeff32698
clean:
	rm -f $(GBUILD)/*.o $(GBIN)/*.exe
    