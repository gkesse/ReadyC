//===============================================
#include "GProcessKeyboard.h"
#include "GKeyboard.h"
#include "GConsole.h"
#include "GBase.h"
//===============================================
static GProcessO* m_GProcessKeyboardO = 0;
//===============================================
static void GProcessKeyboard_Run(int argc, char** argv);
//===============================================
GProcessO* GProcessKeyboard_New() {
    GProcessO* lParent = GProcess_New();
    GProcessKeyboardO* lChild = (GProcessKeyboardO*)malloc(sizeof(GProcessKeyboardO));

    lChild->m_parent = lParent;

    lParent->m_child = lChild;
    lParent->Delete = GProcessKeyboard_Delete;
    lParent->Run = GProcessKeyboard_Run;
    return lParent;
}
//===============================================
void GProcessKeyboard_Delete(GProcessO* obj) {
    GProcess_Delete(obj);
}
//===============================================
GProcessO* GProcessKeyboard() {
    if(m_GProcessKeyboardO == 0) {
        m_GProcessKeyboardO = GProcessKeyboard_New();
    }
    return m_GProcessKeyboardO;
}
//===============================================
static void GProcessKeyboard_Run(int argc, char** argv) {
	int lInt;
	char lBinary[16];
	int lOctal;
	int lHexadecimal;
	float lFloat;
	char lChar;
	char lString[255];
	int lFromBinary;
	char lToBinary[16];

	GConsole()->Print("Saisir un entier decimal: ");
	GKeyboard()->Input("%d", &lInt);
	GConsole()->Print("Saisir un entier binaire: ");
	GKeyboard()->Input("%s", &lBinary);
	GConsole()->Print("Saisir un entier octal: ");
	GKeyboard()->Input("%o", &lOctal);
	GConsole()->Print("Saisir un entier hexadecimal: ");
	GKeyboard()->Input("%x", &lHexadecimal);
	GConsole()->Print("Saisir un reel: ");
	GKeyboard()->Input("%f", &lFloat);
	GKeyboard()->Clear(stdin);
	GConsole()->Print("Saisir un caractere: ");
	GKeyboard()->Input("%c", &lChar);
	GConsole()->Print("Saisir une chaine: ");
	GKeyboard()->Clear(stdin);
	GKeyboard()->Line(lString, 254, stdin);

	GConsole()->Print("\n");
	lFromBinary = GBase()->FromBinary(lBinary);
	GBase()->ToBinary(lHexadecimal, lToBinary);

	GConsole()->Print("Entier decimal: [ %d ]: %d\n", lInt, lInt);
	GConsole()->Print("Entier binaire [ %s ]: [ %X ]: %d\n", lBinary, lFromBinary, lFromBinary);
	GConsole()->Print("Entier octal [ %o ]: %d\n", lOctal, lOctal);
	GConsole()->Print("Entier hexadecimal [ %X ]: [ %s ]: %d\n", lHexadecimal, lToBinary, lHexadecimal);
	GConsole()->Print("Reel: %f\n", lFloat);
	GConsole()->Print("Caractere [ %c ]: %d\n", lChar, lChar);
	GConsole()->Print("Chaine: %s\n", lString);
}
//===============================================
