GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/gp_c

GINCS = \
    -I$(GSRC)/include \
    -I/usr/include/ccv \

GLIBS = \
    -lccv \
    
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c)) \

GCFLAGS = \
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
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@echo
	@./bin/gp_c $(argv)
	@echo
clean:
	rm -f $(GBUILD)/* $(GBIN)/*
