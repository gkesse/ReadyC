GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/GProject.exe

GINCS = \
    -I$(GSRC)/manager \
    -I/opt/gSOAP/gsoap \
    -I/home/centos/Programs/ReadyC/unix/data/soap/src \


GLIBS = \
    -L/home/centos/Programs/ReadyC/unix/data/soap/bin \
    -lGSoap -lsqlite3 \
            
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c))
    
all: $(GOBJS)
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS)
$(GBUILD)/%.o: $(GSRC)/%.c
	gcc -std=c11 -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	gcc -std=c11 -c $< -o $@ $(GINCS)
clean:
	rm -f $(GBUILD)/*.o $(GBIN)/*.exe
    