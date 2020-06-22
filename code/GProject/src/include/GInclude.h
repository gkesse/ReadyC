//===============================================
#ifndef _GInclude_
#define _GInclude_
//===============================================
#if defined(__unix)
//===============================================
#define _D_GNU_SOURCE
#define _USE_MATH_DEFINES
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
//===============================================
#define _GUSE_CCV_ON_
//===============================================
#if defined(_GUSE_CCV_ON_)
#include <ccv.h>
#endif
//===============================================
#endif
//===============================================
#elif defined(__WIN32)
//===============================================
#define _D_GNU_SOURCE
#define _USE_MATH_DEFINES 
//===============================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>
#include <ctype.h>
#endif
//===============================================
#if !defined(TRUE)
#define FALSE (0)
#define TRUE (!FALSE)
//===============================================
#endif
//===============================================
