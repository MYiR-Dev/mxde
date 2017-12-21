#ifndef MXSYSTEMDIALOG_H
#define MXSYSTEMDIALOG_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QDialog>
#include <QPixmap>

#include "mxde.h"
#include "systemactionwidget.h"
#include "systemcontentwidget.h"

class MxSystemDialog : public QDialog
{
    Q_OBJECT
public:

    MxDE                *m_mxde;

    MxSystemDialog(QApplication *app = 0, QWidget *parent = 0);
    ~MxSystemDialog();
    void setApplication(QApplication *app);
    void setDbusProxy(MxDE *mxde);
    void setParentWindow(QWidget *parent);
    void setCurrentLanguage(QString &lang);
    void display();
    void initConnect();

public slots:

    void OnSystemDialogClosed();

private:
    QApplication        *m_app;
    QPixmap             *main_skin_pixmap;


    SystemActionWidget  *m_actionwidget;
    SystemContentWidget *m_contentwidget;
    QWidget             *m_parent;

};

#endif // MXSYSTEMDIALOG_H
