//===============================================
#include "GManager.h"
#include "GPicto.h"
#include "GMap.h"
#include "GList.h"
//===============================================
GDECLARE_MAP(GManager, GVOID_PTR, GVOID_PTR)
GDEFINE_MAP(GManager, GVOID_PTR, GVOID_PTR)
//===============================================
GDECLARE_LIST(GManager, GVOID_PTR)
GDEFINE_LIST(GManager, GVOID_PTR)
//===============================================
static GManagerO* m_GManagerO = 0;
//===============================================
// init
static void GManager_Init(GManagerO* obj);
// data
static void GManager_LoadData();
static void GManager_ShowData(void* data);
// string
static char* GManager_CopyStr(const char* strIn);
static void* GManager_Split(char* strIn, char* sep);
static char* GManager_Trim(char* strIn);
static char* GManager_TrimLeft(char* strIn);
static char* GManager_TrimRight(char* strIn);
static int GManager_GetWidth(char* widthMap, int index, int defaultWidth);
static int GManager_IsNumber(char* strIn);
static char* GManager_Format(const char* format, ...);
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
// terminal
static void GManager_ReadLine(char* buffer, int size);
// free
static void GManager_Free(void* buffer);
//===============================================
GManagerO* GManager_New() {
    GManagerO* lObj = (GManagerO*)malloc(sizeof(GManagerO));

    lObj->Delete = GManager_Delete;
    // data
    lObj->LoadData = GManager_LoadData;
    lObj->ShowData = GManager_ShowData;
    // string
    lObj->CopyStr = GManager_CopyStr;
    lObj->Split = GManager_Split;
    lObj->Trim = GManager_Trim;
    lObj->TrimLeft = GManager_TrimLeft;
    lObj->TrimRight = GManager_TrimRight;
    lObj->GetWidth = GManager_GetWidth;
    lObj->IsNumber = GManager_IsNumber;
    lObj->Format = GManager_Format;
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
    // terminal
    lObj->ReadLine = GManager_ReadLine;
    // free
    lObj->Free = GManager_Free;
    // return
    GManager_Init(lObj);
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
    obj->mgr->app->bg_color = "#103030";
    obj->mgr->app->style_path = GManager_GetEnv("GSTYLE_PATH");
    obj->mgr->app->img_path = GManager_GetEnv("GIMG_PATH");
    obj->mgr->app->img_map = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->picto_map = GMap_New(GManager, GVOID_PTR, GVOID_PTR)();
    obj->mgr->app->path_sep = GManager_GetEnv("GPATH_SEP");
    obj->mgr->app->sqlite_db_path = GManager_GetEnv("GSQLITE_DB_PATH");
    obj->mgr->app->log_on = GManager_GetEnv("GLOG_ON");
    obj->mgr->app->log_mode = GManager_GetEnv("GLOG_MODE");
    obj->mgr->app->log_path = GManager_GetEnv("GLOG_PATH");
}
//===============================================
// data
//===============================================
static void GManager_ShowData(void* data) {
    char* lData = data;
    printf("[%s]\n", lData); 
}
//===============================================
// gtk
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
static void* GManager_Split(char* strIn, char* sep) {
    char* lStrIn = GManager()->CopyStr(strIn);
    char* lPtr = strtok(lStrIn, sep);
    GListO(GManager, GVOID_PTR)* lData = GList_New(GManager, GVOID_PTR)();
    while(1) {
        if(lPtr == 0) break;
        lData->AddData(lData, GManager_CopyStr(lPtr));
        lPtr = strtok(NULL, sep);
    }
    free(lStrIn);
    return lData;
}
//===============================================
static char* GManager_Trim(char* strIn) {     
    return GManager_TrimRight(GManager_TrimLeft(strIn));  
} 
//===============================================
static char* GManager_TrimLeft(char* strIn) {     
    while(isspace(*strIn)) strIn++;     
    return strIn; 
}  
//===============================================
static char* GManager_TrimRight(char* strIn) {     
    char* lBack;
    int lSize = strlen(strIn);
    if(lSize == 0) return(strIn); 
    lBack = strIn + lSize;     
    while(isspace(*--lBack));     
    *(lBack+1) = 0;     
    return strIn; 
}  
//===============================================
static int GManager_GetWidth(char* widthMap, int index, int defaultWidth) {
    GListO(GManager, GVOID_PTR)* lWidthMap = GManager_Split(widthMap, ";");
    int lLength = lWidthMap->Size(lWidthMap);
    if(index >= lLength) {lWidthMap->Delete(lWidthMap, 0); return defaultWidth;}
    char* lWidthId = lWidthMap->GetData(lWidthMap, index);
    if(!GManager_IsNumber(lWidthId)) {lWidthMap->Delete(lWidthMap, 0); return defaultWidth;}
    int lWidth = atoi(lWidthId);
    lWidthMap->Delete(lWidthMap, 0);
    return lWidth;
}
//===============================================
static int GManager_IsNumber(char* strIn) {
    int lSize = strlen(strIn);
    for(int i = 0; i < lSize; i++) {
        if(!isdigit(strIn[i])) return 0;
    }
    return 1;
}
//===============================================
static char* GManager_Format(const char* format, ...) {
    sGApp* lApp = GManager()->mgr->app;
    va_list lArgs;
    va_start(lArgs, format);
    vsprintf(lApp->format, format, lArgs);
    va_end(lArgs);
    return lApp->format;
}
//===============================================
// page
//===============================================
static void GManager_SetPage(char* address) {
    sGApp* lApp = GManager()->mgr->app;
    char* lTitle = lApp->page_map->GetTitle(lApp->page_map, address);
    lApp->page_map->SetCurrentPage(lApp->page_map, address);
    gtk_label_set_text(GTK_LABEL(lApp->title), lTitle);
    lApp->address_key->SetContent(lApp->address_key, address);
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
    sGApp* lApp = GManager()->mgr->app;
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
    sGApp* lApp = GManager()->mgr->app;
    GDir* lDir = g_dir_open(lApp->img_path, 0, NULL);
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lImgMap = lApp->img_map;
    if(lDir != 0) {
        while(1) {
            const char* lName = g_dir_read_name(lDir);
            if(lName == 0) break;
            char lFile[256];
            sprintf(lFile, "%s%s%s", lApp->img_path, lApp->path_sep, lName);
            char* lNameId = GManager()->CopyStr(lName);
            char* lFileId = GManager()->CopyStr(lFile);
            lImgMap->SetData(lImgMap, lNameId, lFileId, lImgMap->EqualChar);
        }
    }
    g_dir_close(lDir);
}
//===============================================
static GtkWidget* GManager_GetImg(char* img, int scale, int width, int height) {
    sGApp* lApp = GManager()->mgr->app;
    GMapO(GManager, GVOID_PTR, GVOID_PTR)* lImgMap = lApp->img_map;
    char* lImgFile = lImgMap->GetData(lImgMap, img, lImgMap->EqualChar);
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
// terminal
//===============================================
static void GManager_ReadLine(char* buffer, int size) {
    fflush(stdout); 
    fgets(buffer, size, stdin); 
    buffer[strlen(buffer)-1] = 0;
}
//===============================================
// free
//===============================================
static void GManager_Free(void* buffer) {
    free(buffer);
}
//===============================================
