GRLIB = /home/centos/Programs/ReadyLib/dev
GSOAP = $(GRLIB)/gsoap/c/unix64/bin
GSRV = srv
GSRC = src
GBUILD = build
GBIN = bin
GTARGET = $(GBIN)/libGSoap2.a

GINCS = \
    -I$(GRLIB)/gsoap/c/include \

GOBJS = \
    $(GBUILD)/soapC.o \
    $(GBUILD)/soapServer.o \
    $(GBUILD)/soapClient.o \

all: soap_lib

soap_lib: $(GOBJS)
	@mkdir -p $(GBIN)
	ar rcs $(GTARGET) $(GOBJS)
$(GBUILD)/soapC.o: $(GSRC)/soapC.c
	@mkdir -p $(GBUILD)
	gcc -c $(GSRC)/soapC.c -o $(GBUILD)/soapC.o $(GINCS)
$(GBUILD)/soapServer.o: $(GSRC)/soapServer.c
	@mkdir -p $(GBUILD)
	gcc -c $(GSRC)/soapServer.c -o $(GBUILD)/soapServer.o $(GINCS)
$(GBUILD)/soapClient.o: $(GSRC)/soapClient.c
	@mkdir -p $(GBUILD)
	gcc -c $(GSRC)/soapClient.c -o $(GBUILD)/soapClient.o $(GINCS)
$(GSRC)/%.c: $(GSRV)/service.h
	$(GSOAP)/soapcpp2 -c -L -d$(GSRC) $(GSRV)/service.h
clean:
	rm -f $(GSRC)/* $(GBUILD)/* $(GBIN)/*
