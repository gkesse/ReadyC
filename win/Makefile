GSRC = ../code/GProject/src
GBIN = bin
GBUILD = build
GTARGET = $(GBIN)/GProject.exe

GINCS = \
    -I$(GSRC)/manager \
    -IC:\Users\Admin\Downloads\sqlite-amalgamation-3_7_0_1
    
GLIBS = \
    -LC:\Users\Admin\Downloads\sqlite-amalgamation-3_7_0_1 \
    -lws2_32 -lsqlite3
    
GOBJS = \
    $(patsubst $(GSRC)/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/*.c)) \
    $(patsubst $(GSRC)/manager/%.c, $(GBUILD)/%.o, $(wildcard $(GSRC)/manager/*.c))
    
all: $(GOBJS)
	gcc -o $(GTARGET) $(GOBJS) $(GLIBS)
$(GBUILD)/%.o: $(GSRC)/%.c
	gcc -c $< -o $@ $(GINCS)
$(GBUILD)/%.o: $(GSRC)/manager/%.c
	gcc -c $< -o $@ $(GINCS)
clean:
	del /q $(GBUILD)\*.o $(GBIN)\*.exe
