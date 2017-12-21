#include "mxsystemdialog.h"
#include "mxmaindialog.h"
#include "systemactionwidget.h"
#include "systemcontentwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>


MxSystemDialog::MxSystemDialog(QApplication *app,  QWidget *parent):QDialog(parent)
{
//    this->setApplication(app);
    this->resize(800,480);
    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);
    this->setWindowOpacity(1);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    m_actionwidget = NULL;
    m_contentwidget = NULL;
    if(m_actionwidget == NULL){
        m_actionwidget = new SystemActionWidget(this,m_app);
        m_actionwidget->setParentWindow(this);
        m_actionwidget->initConnection();

        m_actionwidget->setGeometry(QRect(0,0,800,60));
        QPalette palette_back;
        palette_back.setBrush(QPalette::Background, QBrush(QPixmap(":/res/images/myir/mxde_background1.png")));
        m_actionwidget->setPalette(palette_back);
        m_actionwidget->setPalette(palette_back);
    }

    if(m_contentwidget == NULL)
    {
        m_contentwidget = new SystemContentWidget(this, m_app);
        m_contentwidget->setGeometry(QRect(0,60,800,420));
        m_contentwidget->initUI();
    }




}

MxSystemDialog::~MxSystemDialog()
{

}

void MxSystemDialog::setApplication(QApplication *app)
{
    m_app = app;
}

void MxSystemDialog::setDbusProxy(MxDE *mxde)
{
    m_mxde = mxde;
}

void MxSystemDialog::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}
void MxSystemDialog::display(){
    if (this->isHidden()) {
        int windowWidth, windowHeight = 0;
            windowWidth = QApplication::desktop()->screenGeometry(0).width();
            windowHeight = QApplication::desktop()->screenGeometry(0).height();
            this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
        this->show();
        this->raise();
    //        QTimer::singleShot(100, this, SLOT(startDbusDaemon()));
    }

    else {
        this->hide();
    }
}
void MxSystemDialog::OnSystemDialogClosed()
{
    m_parent->show();
    m_parent->raise();
    this->close();
}
