GSRV = srv/service.h
GSRC = src
GBUILD = build
GBIN = bin
GTARGET = $(GBIN)/libGSoap2.a
GSOAP = /opt/gSOAP/gsoap

GINCS = \
    -I/opt/gSOAP/gsoap/

GOBJS = \
    $(GBUILD)/soapC.o \
    $(GBUILD)/soapServer.o \
    $(GBUILD)/soapClient.o \
    $(GBUILD)/stdsoap2.o \
    
soap_src:
	soapcpp2 -c -L -d$(GSRC) $(GSRV)
soap_lib: $(GOBJS)
	ar rcs $(GTARGET) $(GOBJS)
$(GBUILD)/soapC.o: $(GSRC)/soapC.c
	gcc -c $(GSRC)/soapC.c -o $(GBUILD)/soapC.o $(GINCS)
$(GBUILD)/soapServer.o: $(GSRC)/soapServer.c
	gcc -c $(GSRC)/soapServer.c -o $(GBUILD)/soapServer.o $(GINCS)
$(GBUILD)/soapClient.o: $(GSRC)/soapClient.c
	gcc -c $(GSRC)/soapClient.c -o $(GBUILD)/soapClient.o $(GINCS)
$(GBUILD)/stdsoap2.o: $(GSOAP)/stdsoap2.c
	gcc -c $(GSOAP)/stdsoap2.c -o $(GBUILD)/stdsoap2.o $(GINCS)
clean:
	rm -f $(GSRC)/* $(GBUILD)/* $(GBIN)/*
