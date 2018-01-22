#ifndef SYSTEMCONTENTWIDGET_H
#define SYSTEMCONTENTWIDGET_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QList>
#include <QSplitter>
#include <QLabel>
#include <QVBoxLayout>
#include "mxde.h"
#include "mxapplication.h"
#include "basewidget.h"
class SystemContentWidget : public BaseWidget
{
    Q_OBJECT
public:
    MxDE    *m_mxde;
    SystemContentWidget(QWidget *parent = 0,MxApplication *obj = 0, int width = 0, int height = 0);
    ~SystemContentWidget();
    void setApplication(MxApplication *app);
    void setDbusProxy(MxDE *mxde);
    void setParentWindow(QWidget *parent);
    void initUI();
    void initConnection();
    void display();

signals:
    void clickSerialPortCombobox();

public slots:

    void changeInfoPage(int);

private:
    QWidget                 *m_parent;
    MxApplication           *m_app;
    int                      m_width;
    int                      m_height;
    QGridLayout     *mainLayout;
    QLabel* m_info_label;
    QListWidget *m_category_widget;


};

#endif // SYSTEMCONTENTWIDGET_H
