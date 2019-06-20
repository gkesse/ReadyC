//===============================================
#ifndef _GKeyboard_
#define _GKeyboard_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _GKeyboardO GKeyboardO;
//===============================================
struct _GKeyboardO {
    void (*Delete)();
    int (*Input)(const char* template, ...);
    char* (*Line)(char* str, int size, FILE* stream);
    int (*Clear)(FILE* stream);
};
//===============================================
GKeyboardO* GKeyboard_New();
void GKeyboard_Delete();
GKeyboardO* GKeyboard();
//===============================================
#endif
//===============================================
