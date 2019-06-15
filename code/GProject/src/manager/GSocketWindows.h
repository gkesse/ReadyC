#ifndef _GSocketWindows_
#define _GSocketWindows_
//===============================================
#include "GSocket.h"
//===============================================
typedef struct _GSocketWindowsO GSocketWindowsO;
//===============================================
struct _GSocketWindowsO {
    GSocketO* m_parent;
#if defined(__WIN32)
    WSADATA m_wsaData;
    SOCKET m_socket;
    SOCKADDR_IN m_address;
    SOCKET m_socket2;
    SOCKADDR_IN m_address2;
#endif
};
//===============================================
GSocketO* GSocketWindows_New();
void GSocketWindows_Delete(GSocketO* obj);
GSocketO* GSocketWindows();
//===============================================
#endif
//===============================================
