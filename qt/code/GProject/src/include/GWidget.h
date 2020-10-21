//===============================================
#ifndef _GWidget_
#define _GWidget_
//===============================================
#include "GInclude.h"
//===============================================
class GWidget : public QFrame {
    Q_OBJECT
    
public:
    GWidget(QWidget* parent = 0);
    virtual ~GWidget();
    static GWidget* Create(QString key, QWidget* parent = 0);
    
public:
    virtual void addItem(QString key, QString text);
    virtual void addItem(QString key, QString text, QIcon icon);
    virtual void addItem(QString key, QString text, QIcon icon, int width, int height);
    virtual void addPage(QString key, QWidget* widget);

public slots:
    virtual void slotItemClick();

signals:
    void emitItemClick();
};
//===============================================
#endif
//===============================================
