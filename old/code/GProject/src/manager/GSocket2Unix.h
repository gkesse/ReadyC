#ifndef _GSocket2Unix_
#define _GSocket2Unix_
//===============================================
#include "GSocket2.h"
#include "GMap.h"
//===============================================
typedef struct _GSocket2UnixO GSocket2UnixO;
typedef struct _GMapO_GSocket2Unix_GCHAR_PTR_GINT_PTR GMapO_GSocket2Unix_GCHAR_PTR_GINT_PTR;
typedef struct _GMapO_GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR GMapO_GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR;
typedef struct _GMapO_GSocket2Unix_GCHAR_PTR_GFDSET_PTR GMapO_GSocket2Unix_GCHAR_PTR_GFDSET_PTR;
//===============================================
struct _GSocket2UnixO {
    GSocket2O* m_parent;
#if defined(__unix)
    GMapO(GSocket2Unix_GCHAR_PTR_GINT_PTR)* m_socketMap;
    GMapO(GSocket2Unix_GCHAR_PTR_GSOCKADDRIN_PTR)* m_addressMap;
    GMapO(GSocket2Unix_GCHAR_PTR_GFDSET_PTR)* m_fdsetMap;
#endif
};
//===============================================
GSocket2O* GSocket2Unix_New();
void GSocket2Unix_Delete(GSocket2O* obj);
GSocket2O* GSocket2Unix();
//===============================================
#endif
//===============================================
