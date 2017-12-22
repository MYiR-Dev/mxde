#include "mxmaindialog.h"
#include "systemactionwidget.h"
#include "systemcontentwidget.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QDialog>


MxMainDialog::MxMainDialog(QApplication *app,  QWidget *parent):QDialog(parent)
{
    m_mxde = new MxDE(this);
    this->setApplication(app);
    this->resize(800,480);
    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);
//    this->setWindowOpacity(1);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    m_actionwidget = NULL;
    m_contentwidget = NULL;

}

MxMainDialog::~MxMainDialog()
{
    if(m_actionwidget != NULL){
        delete m_actionwidget;
        m_actionwidget = NULL;
    }
    if(m_contentwidget != NULL){
        delete m_contentwidget;
        m_contentwidget = NULL;
    }
}

void MxMainDialog::setApplication(QApplication *app)
{
    m_app = app;
}

void MxMainDialog::setDbusProxy(MxDE *mxde)
{
    m_mxde = mxde;
}

void MxMainDialog::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}

void MxMainDialog::display(){
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
        m_contentwidget->setDbusProxy(m_mxde);
        m_contentwidget->loadLeds();
        m_contentwidget->initUI();
        m_contentwidget->setApplication(m_app);
        m_contentwidget->setParentWindow(this);
        connect(this, SIGNAL(LedBrightnessChanged(const QString)), m_contentwidget, SLOT(onLedBrightnessChanged(const QString)));
    }

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
void MxMainDialog::OnSystemDialogClosed()
{
    if(m_parent){
        m_parent->show();
        m_parent->raise();
    }
    this->close();
}

void MxMainDialog::onLedBrightnessChanged(const QString &message)
{
    emit this->LedBrightnessChanged(message);
}
