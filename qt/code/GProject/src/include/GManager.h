//===============================================
#ifndef _GManager_
#define _GManager_
//===============================================
#include "GInclude.h"
//===============================================
typedef struct _sGManager sGManager;
typedef struct _sGApp sGApp;
typedef struct _sGQt sGQt;
typedef struct _sGTitleBar sGTitleBar;
typedef struct _sGMenuIcon sGMenuIcon;
//===============================================
class GManager {
private:
    GManager();
    
public:
    ~GManager();
    static GManager* Instance();
    sGManager* getData();
    // style
    void loadStyle();
    // picto
    QIcon loadPicto(int picto, QColor color = "white");
    // font
    void listFont();
    void loadFont();
    // page
    void setCuurentPage(QString key);

private:
    static GManager* m_instance;
    sGManager* m_mgr;
    QtAwesome* m_QtAwesome;
};
//===============================================
struct _sGManager {
    sGApp* app;
    sGQt* qt;
    sGTitleBar* title_bar;
    sGMenuIcon* menu_icon;
};
//===============================================
struct _sGApp {
    QString app_name;
};
//===============================================
struct _sGQt {
    QString title;
    QString style_file;
    QString font_list;
    QStackedWidget* page_map;
    QMap<QString, int> page_id;
    int icon;
    QColor icon_color;
    int width;
    int height;
};
//===============================================
struct _sGTitleBar {
    QString icon_file;
    QString click_id;
    QString url;
    QColor color;
    QString update;
    QString update_img;
    int logo_size;
    int icon_size;
    int update_fa;
};
//===============================================
struct _sGMenuIcon {
    QColor icon_color;
    int icon_size;
    int col_max;
    int default_icon;
};
//===============================================
#endif
//===============================================
