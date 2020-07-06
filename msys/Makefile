GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/gp_c 

GINCS = \
    -I$(GSRC)/include \
    -I./data/gsoap/src \
    -I/mingw32/include \
    -I/mingw32/include/mariadb \
    -I/mingw32/include/dbus-1.0 \
    -I/mingw32/lib/dbus-1.0/include \

GLIBS = \
    -L./data/gsoap/bin \
    -L/mingw32/lib \
    -lsqlite3 -lmysqlclient -ldbus-1 -lgsoap -lgsoap2 \
    
    
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c)) \

GCFLAGS = \
    -std=gnu18 \
    -W -Wall \
    
all: clean_exe compile run
 
compile: $(GOBJS)
	@if ! [ -d "$(GBIN)" ] ; then mkdir -p $(GBIN) ; fi
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@echo
	@$(GTARGET) $(argv)
	@echo
clean_exe:
	rm -f $(GBIN)/*
clean:
	rm -f $(GBUILD)/* $(GBIN)/*
