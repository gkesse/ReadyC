GRLIB = C:\Users\Admin\Downloads\Programs\ReadyLib\dev
GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/gz_c.exe

GINCS = \
    -I$(GSRC)\include \
    -I$(GRLIB)\sqlite\3.29.0\mingw\include \

GLIBS = \
    -L$(GRLIB)\sqlite\3.29.0\mingw\lib \
    -lws2_32 -lsqlite3 \

GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c))

GCFLAGS = \
    -std=gnu18 \
    -W -Wall \
    -Wno-unused-parameter \
    -Wno-format-overflow \
    -Wno-unused-function \

all: clean_exe compile run

compile: $(GOBJS)
	@if not exist "$(GBIN)" @mkdir $(GBIN)
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS) 
$(GBUILD)/%.o: $(GSRC)/%.c
	@if not exist "$(GBUILD)" @mkdir $(GBUILD)
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	@if not exist "$(GBUILD)" @mkdir $(GBUILD)
	gcc $(GCFLAGS) -c $< -o $@ $(GINCS)
run:
	@echo.
	@$(GTARGET) $(argv)
	@echo.
clean_exe:
	del /q $(GBIN)\*.exe
clean:
	del /q $(GBUILD)\*.o $(GBIN)\*.exe
