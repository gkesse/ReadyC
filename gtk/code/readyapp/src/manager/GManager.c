//===============================================
#define _GMAP_EQUAL_CHAR_
//===============================================
#include "GManager.h"
#include "GPicto.h"
#include "GMap.h"
//===============================================
GDECLARE_MAP(GManager, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GManager, GVOID_PTR, GVOID_PTR)
//===============================================
#define B_STRING (256)
//===============================================
static GManagerO* m_GManagerO = 0;
//===============================================
// init
static void GManager_Init(GManagerO* obj);
// data
static sGManager* GManager_GetData();
static void GManager_LoadData();
// string
static char* GManager_CopyStr(const char* strIn);
static int GManager_SplitCount(char* strIn, char* sep);
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index);
// page
static void GManager_SetPage(char* address);
// layout
static void GManager_ClearLayout(GtkWidget* layout);
// widget
static void GManager_SetColor(char* key, GtkWidget* widget, char* color, int state);
// font
static void GManager_SetFont(GtkWidget* widget, char* font);
// style
static void GManager_LoadStyle();
// env
static char* GManager_GetEnv(char* key);
// img
static void GManager_LoadImg();
static GtkWidget* GManager_GetImg(char* img, int scale, int width, int height);
// picto
static void GManager_LoadPicto();
static char* GManager_GetPicto(char* key);
// button
static GtkWidget* GManager_Button(char* icon, char* text, int space, int font);
static GtkWidget* GManager_Button2(char* img, int scale, int width, int height, char* text, int space);
// sapce
static GtkWidget* GManager_SpaceH(int space);
static GtkWidget* GManager_SpaceV(int space);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));
    GManager_Init(lObj);
    lObj->Delete = GManager_Delete;
    // data
    lObj->GetData = GManager_GetData;
    lObj->LoadData = GManager_LoadData;
    // string
    lObj->CopyStr = GManager_CopyStr;
    lObj->SplitCount = GManager_SplitCount;
    lObj->SplitGet = GManager_SplitGet;
    // page
    lObj->SetPage = GManager_SetPage;
    // layout
    lObj->ClearLayout = GManager_ClearLayout;
    // widget
    lObj->SetColor = GManager_SetColor;
    // font
    lObj->SetFont = GManager_SetFont;
    // style
    lObj->LoadStyle = GManager_LoadStyle;
    // env
    lObj->GetEnv = GManager_GetEnv;
    // img
    lObj->LoadImg = GManager_LoadImg;
    lObj->GetImg = GManager_GetImg;
    // picto
    lObj->LoadPicto = GManager_LoadPicto;
    lObj->GetPicto = GManager_GetPicto;
    // button
    lObj->Button = GManager_Button;
    lObj->Button2 = GManager_Button2;
    // space
    lObj->SpaceH = GManager_SpaceH;
    lObj->SpaceV = GManager_SpaceV;
    // return
    return lObj;
}
//===============================================
void GManager_Delete() {

}
//===============================================
GManagerO* GManager() {
    if(m_GManagerO == 0) {
        m_GManagerO = GManager_New();
    }
    return m_GManagerO;
}
//===============================================
// init
//===============================================
static void GManager_Init(GManagerO* obj) {
    // manager
    obj->mgr = (sGManager*)malloc(sizeof(sGManager));
    // app
    obj->mgr->app = (sGApp*)malloc(sizeof(sGApp));
    obj->mgr->app->app_name = "ReadyApp";
    obj->mgr->app->win_width = 600;
    obj->mgr->app->win_height = 330;
    obj->mgr->app->page_id = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->title_map = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->bg_color = "#103030";
    obj->mgr->app->style_path = GManager_GetEnv("GSTYLE_PATH");
    obj->mgr->app->img_path = GManager_GetEnv("GIMG_PATH");
    obj->mgr->app->img_map = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->picto_map = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->path_sep = GManager_GetEnv("GPATH_SEP");
}
//===============================================
// data
//===============================================
static sGManager* GManager_GetData() {
    return m_GManagerO->mgr;
}
//===============================================
static void GManager_LoadData() {
    g_object_set(gtk_settings_get_default(), "gtk-button-images", 1, NULL);
}
//===============================================
// string
//===============================================
static char* GManager_CopyStr(const char* strIn) {
    int lSize = strlen(strIn);
    char* lStr = (char*)malloc(sizeof(char)*(lSize+1));
    strcpy(lStr, strIn);
    return lStr;
}
//===============================================
static int GManager_SplitCount(char* strIn, char* sep) {
    int lPos = 0;
    int lCount = 0;

    while(strIn[lPos] != 0) {
        char lChar = strIn[lPos];
        char* lSearch = strchr(sep, lChar);
        if(lSearch != 0) lCount++;
        lPos++;
    }
    lCount += 1;
    return lCount;
}
//===============================================
static void GManager_SplitGet(char* strIn, char* strOut, char* sep, int index) {
    int lPos = 0;
    int lOut = 0;
    int lCount = 0;
    int lFlag = 0;
    char strIn2[B_STRING+1];
    strcpy(strIn2, strIn);

    while(strIn2[lPos] != 0) {
        if(lFlag == 0) {
            if(lCount == index) lFlag = 1;
            else lFlag = 2;
        }
        if(lFlag == 1) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) break;
            strOut[lOut] = lChar;
            lPos++; lOut++;
        }
        if(lFlag == 2) {
            char lChar = strIn2[lPos];
            char* lSearch = strchr(sep, lChar);
            if(lSearch != 0) lCount++;
            lPos++;
            lFlag = 0;
        }
    }
    strOut[lOut] = 0;
}
//===============================================
// page
//===============================================
static void GManager_SetPage(char* address) {
    sGApp* lApp = GManager()->GetData()->app;
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lPageId = lApp->page_id;
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lTitleMap = lApp->title_map;
    int lPageIndex = (int)lPageId->GetData(lPageId, address, GMAP_EQUAL_CHAR);
    char* lTitle = lTitleMap->GetData(lTitleMap, address, GMAP_EQUAL_CHAR);
    lApp->page_map->SetCurrentIndex(lApp->page_map, lPageIndex);
    gtk_label_set_text(GTK_LABEL(lApp->title), lTitle);
    lApp->address_key->SetContent(lApp->address_key, "home/login");
    gtk_entry_set_text(GTK_ENTRY(lApp->address_bar), address);
    gtk_widget_show_all(lApp->address_key->widget);
}
//===============================================
// layout
//===============================================
static void GManager_ClearLayout(GtkWidget* layout) {
    GList* lChildren = gtk_container_get_children(GTK_CONTAINER(layout));
    for(GList* lChild = lChildren; lChild != 0; lChild = g_list_next(lChild)) {
        gtk_widget_destroy(GTK_WIDGET(lChild->data));
    }
    g_list_free(lChildren);
}
//===============================================
// widget
//===============================================
static void GManager_SetColor(char* key, GtkWidget* widget, char* color, int state) {
    if(!strcmp(key, "bg")) {
        GdkRGBA lColor;
        gdk_rgba_parse(&lColor, color);
        gtk_widget_override_background_color(widget, state, &lColor);
    }
    else if(!strcmp(key, "fg")) {
        GdkColor lColor;
        gdk_color_parse(color, &lColor);
        gtk_widget_modify_fg(widget, state, &lColor);
    }
}
//===============================================
// font
//===============================================
static void GManager_SetFont(GtkWidget* widget, char* font) {
    PangoFontDescription* lFont = pango_font_description_from_string(font);
    gtk_widget_modify_font(widget, lFont);
    pango_font_description_free(lFont);
}
//===============================================
// style
//===============================================
static void GManager_LoadStyle() {
    sGApp* lApp = GManager()->GetData()->app;
    GtkCssProvider* lCssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(lCssProvider, lApp->style_path, 0);
    GdkScreen* lScreen = gdk_screen_get_default();
    gtk_style_context_add_provider_for_screen(lScreen, GTK_STYLE_PROVIDER(lCssProvider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION); 
}
//===============================================
// env
//===============================================
static char* GManager_GetEnv(char* key) {
    char* lValue = getenv(key);
    return lValue;
}
//===============================================
// img
//===============================================
static void GManager_LoadImg() {
    sGApp* lApp = GManager()->GetData()->app;
    GDir* lDir = g_dir_open(lApp->img_path, 0, NULL);
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lImgMap = lApp->img_map;
    if(lDir != 0) {
        while(1) {
            const char* lName = g_dir_read_name(lDir);
            if(lName == 0) break;
            char lFile[B_STRING+1];
            sprintf(lFile, "%s%s%s", lApp->img_path, lApp->path_sep, lName);
            char* lNameId = GManager()->CopyStr(lName);
            char* lFileId = GManager()->CopyStr(lFile);
            lImgMap->SetData(lImgMap, lNameId, lFileId, GMAP_EQUAL_CHAR);
        }
    }
    g_dir_close(lDir);
}
//===============================================
static GtkWidget* GManager_GetImg(char* img, int scale, int width, int height) {
    sGApp* lApp = GManager()->GetData()->app;
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lImgMap = lApp->img_map;
    char* lImgFile = lImgMap->GetData(lImgMap, img, GMAP_EQUAL_CHAR);
    GdkPixbuf* lPixbuf = gdk_pixbuf_new_from_file(lImgFile, NULL);
    if(scale != 0) lPixbuf = gdk_pixbuf_scale_simple(lPixbuf, width, height, GDK_INTERP_BILINEAR);
    GtkWidget* lImage = gtk_image_new();
    gtk_image_set_from_pixbuf(GTK_IMAGE(lImage), lPixbuf);
    return lImage;
}
//===============================================
// picto
//===============================================
static void GManager_LoadPicto() {
    GPicto()->Load();
}
//===============================================
static char* GManager_GetPicto(char* key) {
    return GPicto()->Get(key);
}
//===============================================
// button
//===============================================
static GtkWidget* GManager_Button(char* icon, char* text, int space, int font) {
    GtkWidget* lButton = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(lButton), GTK_RELIEF_NONE);
    GtkWidget* lLayout = gtk_hbox_new(0, 0);
    gtk_widget_set_name(lLayout, "layout");
    GtkWidget *lIcon, *lText;
    char lFont[256] = "FontAwesome";
    if(font != 0) sprintf(lFont, "%s %d", lFont, font);
    if(icon != 0) lIcon = gtk_label_new(0);
    if(text != 0) lText = gtk_label_new(0);
    if(icon != 0) GManager()->SetFont(lIcon, lFont);
    if(icon != 0) gtk_label_set_markup(GTK_LABEL(lIcon), GManager()->GetPicto(icon));
    if(text != 0) gtk_label_set_text(GTK_LABEL(lText), text);
    if(icon != 0) gtk_box_pack_start(GTK_BOX(lLayout), lIcon, 0, 0, 0);
    if(space != 0) gtk_box_pack_start(GTK_BOX(lLayout), GManager()->SpaceH(space), 0, 0, 0);
    if(text != 0) gtk_box_pack_start(GTK_BOX(lLayout), lText, 1, 1, 0);
    gtk_container_add(GTK_CONTAINER(lButton), lLayout);
    return lButton;
}
//===============================================
static GtkWidget* GManager_Button2(char* img, int scale, int width, int height, char* text, int space) {
    GtkWidget* lButton = gtk_button_new();
    gtk_button_set_relief(GTK_BUTTON(lButton), GTK_RELIEF_NONE);
    GtkWidget* lLayout = gtk_hbox_new(0, 0);
    gtk_widget_set_name(lLayout, "layout");
    GtkWidget *lImg, *lText;
    if(img != 0) lImg = GManager()->GetImg(img, scale, width, height);
    if(text != 0) lText = gtk_label_new(0);
    if(text != 0) gtk_label_set_text(GTK_LABEL(lText), text);
    if(img != 0) gtk_box_pack_start(GTK_BOX(lLayout), lImg, 0, 0, 0);
    if(space != 0) gtk_box_pack_start(GTK_BOX(lLayout), GManager()->SpaceH(space), 0, 0, 0);
    if(text != 0) gtk_box_pack_start(GTK_BOX(lLayout), lText, 1, 1, 0);
    gtk_container_add(GTK_CONTAINER(lButton), lLayout);
    return lButton;
}
//===============================================
// space
//===============================================
static GtkWidget* GManager_SpaceH(int space) {
    GtkWidget* lSpace = gtk_hbox_new(0, 0);
    gtk_widget_set_margin_left(lSpace, space);
    return lSpace;
}
//===============================================
static GtkWidget* GManager_SpaceV(int space) {
    GtkWidget* lSpace = gtk_vbox_new(0, 0);
    gtk_widget_set_margin_top(lSpace, space);
    return lSpace;
}
//===============================================
