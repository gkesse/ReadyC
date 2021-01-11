//===============================================
#include "GManager.h"
//===============================================
GManager* GManager::m_instance = 0;
//===============================================
GManager::GManager() {
    // manager
    m_mgr = new sGManager;
    // app
    m_mgr->app = new sGApp;
    m_mgr->app->app_name = "ReadyApp";
    // qt
    m_mgr->qt = new sGQt;
    m_mgr->qt->title = m_mgr->app->app_name;
    m_mgr->qt->style_file = ":/css/style.css";
    m_mgr->qt->font_list = "Lobster;Akronim;Allan;Aclonica";
    m_mgr->qt->width = 640;
    m_mgr->qt->height = 480;
    m_mgr->qt->icon = fa::wifi;
    m_mgr->qt->icon_color = "white";
    // title_bar
    m_mgr->title_bar = new sGTitleBar;
    m_mgr->title_bar->icon_file = ":/img/logo_icon.png";
    m_mgr->title_bar->icon_size = 16;
    m_mgr->title_bar->logo_size = 20;
    m_mgr->title_bar->color = "white";
    m_mgr->title_bar->url = "https://readydev.ovh";
    // menu_icon
    m_mgr->menu_icon = new sGMenuIcon;
    m_mgr->menu_icon->icon_color = "white";
    m_mgr->menu_icon->icon_size = 50;
    m_mgr->menu_icon->col_max = 5;
    m_mgr->menu_icon->default_icon = fa::home;
    // page
    m_mgr->page = new sGPage;
    m_mgr->page->icon_color = "white";
    m_mgr->page->icon_size = 25;
    m_mgr->page->list_icon = fa::book;
    // qt_awesoome
    m_QtAwesome = new QtAwesome(qApp);
}
//===============================================
GManager::~GManager() {
    
}
//===============================================
GManager* GManager::Instance() {
    if(m_instance == 0) {
        m_instance = new GManager;
    }
    return m_instance;
}
//===============================================
sGManager* GManager::getData() {
    return m_mgr;
}
//===============================================
// style
//===============================================
void GManager::loadStyle() {
    QFile lFile(m_mgr->qt->style_file);
    lFile.open(QFile::ReadOnly);
    QString lStyleSheet = QLatin1String(lFile.readAll());
    qApp->setStyleSheet(lStyleSheet);
}
//===============================================
// picto
//===============================================
QIcon GManager::loadPicto(int picto, QColor color) {
    m_QtAwesome->initFontAwesome();
    m_QtAwesome->setDefaultOption("color", color);
    m_QtAwesome->setDefaultOption("color-active", color);
    return  m_QtAwesome->icon(picto);
}
//===============================================
// font
//===============================================
void GManager::listFont() {
    QFontDatabase lFontDb;
    for(int i = 0; i < lFontDb.families().size(); i++) {
        qDebug() << lFontDb.families().at(i);
    }
}
//===============================================
void GManager::loadFont() {
    QStringList lFontMap = m_mgr->qt->font_list.split(";");
    for(int i = 0; i < lFontMap.count(); i++) {
        QString lFontName = lFontMap.at(i);
        QString lFont = ":/font/" + lFontName + ".ttf";
        QFontDatabase::addApplicationFont(lFont);
    }
}
//===============================================
// font
//===============================================
void GManager::setCurrentPage(QString key) {
    int lPageId = m_mgr->qt->page_id.value(key, -1);
    if(lPageId == -1) {
        m_mgr->qt->address->setText(m_mgr->qt->address_url);
        return;
    }
    m_mgr->qt->page_map->setCurrentIndex(lPageId);
    m_mgr->qt->address->setText(key);
    m_mgr->qt->address_url = key;
}

//===============================================
