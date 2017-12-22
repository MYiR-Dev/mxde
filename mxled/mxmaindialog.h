#ifndef MXMAINDIALOG_H
#define MXMAINDIALOG_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QDialog>
#include <QPixmap>

#include "mxde.h"
#include "systemactionwidget.h"
#include "systemcontentwidget.h"

class MxMainDialog : public QDialog
{
    Q_OBJECT

public:

    MxDE                *m_mxde;

    MxMainDialog(QApplication *app = 0, QWidget *parent = 0);
    ~MxMainDialog();
    void setApplication(QApplication *app);
    void setDbusProxy(MxDE *mxde);
    void setParentWindow(QWidget *parent);
    void setCurrentLanguage(QString &lang);
    void display();
    void initConnect();

signals:
    void LedBrightnessChanged(const QString &message);

public slots:
    void OnSystemDialogClosed();
    void onLedBrightnessChanged(const QString &message);

private:
    QApplication        *m_app;
    QPixmap             *main_skin_pixmap;


    SystemActionWidget  *m_actionwidget;
    SystemContentWidget *m_contentwidget;
    QWidget             *m_parent;

};

#endif // MXMAINDIALOG_H
