GSRC = .
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)\gz_app.exe

GOBJS = \
    $(GBUILD)\main.o
    
all: clean compile run

compile: $(GOBJS)
	@if not exist $(GBIN) ( mkdir $(GBIN) )
	gcc -o $(GTARGET) $(GOBJS)
$(GBUILD)\main.o: $(GSRC)\main.c
	@if not exist $(GBUILD) ( mkdir $(GBUILD) )
	gcc -c $(GSRC)\main.c -o $(GBUILD)\main.o
run:
	@echo.
	$(GTARGET)
	@echo.
clean:
	del /q $(GBUILD)\* $(GBIN)\*
