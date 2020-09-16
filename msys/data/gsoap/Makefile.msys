GSRV = srv
GSRC = src
GBUILD = build
GBIN = bin
GTARGET = $(GBIN)/libgsoap2.a

GINCS = \
    -I/mingw64/include \

GOBJS = \
    $(GBUILD)/soapC.o \
    $(GBUILD)/soapServer.o \
    $(GBUILD)/soapClient.o \

GCFLAGS = \
    -std=gnu18 \
    -W -Wall \
    -DWITH_NO_C_LOCAL \

all: clean soap_lib

soap_lib: $(GOBJS)
	@if ! [ -d "$(GBIN)" ] ; then mkdir -p $(GBIN) ; fi
	ar rcs $(GTARGET) $(GOBJS)
$(GBUILD)/soapC.o: $(GSRC)/soapC.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $(GSRC)/soapC.c -o $(GBUILD)/soapC.o $(GINCS)
$(GBUILD)/soapServer.o: $(GSRC)/soapServer.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $(GSRC)/soapServer.c -o $(GBUILD)/soapServer.o $(GINCS)
$(GBUILD)/soapClient.o: $(GSRC)/soapClient.c
	@if ! [ -d "$(GBUILD)" ] ; then mkdir -p $(GBUILD) ; fi
	gcc $(GCFLAGS) -c $(GSRC)/soapClient.c -o $(GBUILD)/soapClient.o $(GINCS)
$(GSRC)/%.c: $(GSRV)/service.h
	@if ! [ -d "$(GSRC)" ] ; then mkdir -p $(GSRC) ; fi
	@soapcpp2 -c -L -d$(GSRC) $(GSRV)/service.h
clean:
	rm -f $(GSRC)/* $(GBUILD)/* $(GBIN)/*
