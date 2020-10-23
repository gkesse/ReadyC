//===============================================
#include "GManager.h"
#include "GWidget.h"
//===============================================
int main(int argc, char** argv) {
    QApplication app(argc, argv);
    GManager::Instance()->loadFont();
    GManager::Instance()->loadStyle();
    GWidget* lWindow = GWidget::Create("window");
    lWindow->show();
    return app.exec();
}
//===============================================
