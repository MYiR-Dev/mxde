/******************************************************************************
* Copyright (C), 2016-2017, Sunny.Guo
* FileName:
* Author: Sunny.Guo
* Version: 1.0
* Date:
* Description:
*
* History:
*  <author>  	<time>   	<version >   	<desc>
*  Sunny.Guo   	19/01/2017      1.0     	create this moudle
*
* Licensed under GPLv2 or later, see file LICENSE in this source tree.
*******************************************************************************/
#include "systemcontentwidget.h"
#include "mxledindicator.h"
#include "mxde.h"

#include <QObject>
#include <QtWidgets>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QDirIterator>
#include <QStringList>
#include <QPalette>

char *led_name[5];
char *led_statu[5];

SystemContentWidget::SystemContentWidget(QWidget *parent, QObject *obj):BaseWidget(parent,obj)
{
    this->setFixedSize(800, 420);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);
}

SystemContentWidget::~SystemContentWidget()
{
}

void SystemContentWidget::initUI()
{
        createHorizontalGroupBox();

        QGridLayout *mainLayout = new QGridLayout;

        bigEditor = new QTextEdit;
        bigEditor->setReadOnly(true);
        bigEditor->setStyleSheet("border:none");

        getBoardLedInfo();

        QLabel *m = new QLabel();
        m->setPixmap(QPixmap("/usr/share/myir/MYD-AM335Xs.jpg"));
        m->setAlignment(Qt::AlignCenter);

        mainLayout->addWidget(horizontalGroupBox,0,0,1,3,Qt::AlignCenter);
//        mainLayout->addWidget(m,1,0,2,1);
        mainLayout->addWidget(bigEditor,1,1,2,1);

//        mainLayout->addWidget(buttonBox);
        setLayout(mainLayout);

//        setWindowTitle(tr("Basic Layouts"));
//        QDesktopWidget *desk = QApplication::desktop();
//        QRect deskRect = desk->availableGeometry();
//        this->resize(QSize(800,480));
//        this->move((deskRect.width()-this->width())/2, (deskRect.height()-this->height())/2);



        connect(this, SIGNAL(click_Button(int)), this, SLOT(on_click_Button(int)));
        //connect(m_mxde->m_dbus->mxde_session_iface, SIGNAL(sigLedBrightnessChanged(QString)), this, SLOT(onLedBrightnessChanged(QString)));

}

void SystemContentWidget::getBoardLedInfo()
{
    QFile f("/usr/share/myir/board_led_info");
    QTextCodec *codec = QTextCodec::codecForName("UTF8");

    if(!f.open(QIODevice::ReadOnly | QIODevice::Text))
    {
         qDebug()  << "Open failed.";

    }
#if 1
    QTextStream txtInput(&f);
    txtInput.setCodec(codec);
    QString lineStr;
    while(!txtInput.atEnd())
    {
       bigEditor->append(codec->fromUnicode(txtInput.readLine()));

    }

    //f.close();
#endif

}
//! [5]
void SystemContentWidget::getLedNameAndStatus()
{
    QString led_list =  m_mxde->callGetLedList();

    qDebug() << led_list;

    m_ledList = led_list.split("\n");
    m_ledNum = m_ledList.count()-1;
    qDebug("led_num:%d",m_ledNum);


    for(int i=0;i<m_ledNum;i++)
    {

         QStringList strstrlist=m_ledList.at(i).split(" ");
         for(int j=0;j<strstrlist.count();)
         {

          led_name[i] = strdup(strstrlist.at(j++).toLocal8Bit().data());
          led_statu[i] = strdup(strstrlist.at(j++).toLocal8Bit().data());
          qDebug("%s %s",led_name[i],led_statu[i]);
         }
    }
}
void SystemContentWidget::loadLeds()
{
    getLedNameAndStatus();
    for (int i = 0; i < m_ledNum; ++i){
        MxLedIndicator *led = new MxLedIndicator(this);
        QString ledName = QString(led_name[i]);
        led->setLedSize(30);
        led->setLedName(ledName);
        QString str = led_statu[i];
        if( str.toInt() > 1)
        {
            led->setState(0);
            m_mxde->callSetLedBrightness(ledName,0);
        }
        else
        {
            led->setState(str.toInt());
        }
        leds.append(led);
    }
}


void SystemContentWidget::createHorizontalGroupBox()
{
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    horizontalGroupBox = new QGroupBox();
    QHBoxLayout *layout = new QHBoxLayout;

    for (int i = 0; i < leds.size(); ++i) {
 //      buttons[i] = new QPushButton(leds.at(i)->getLedName());
        QVBoxLayout *ledLayout = new QVBoxLayout();
        QPushButton *ledButton = new QPushButton();
        ledButton->setText(leds.at(i)->getLedName());
        connect(ledButton, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(ledButton, QString::number(i, 10));

        ledLayout->addWidget(leds.at(i),0,Qt::AlignHCenter);
        ledLayout->addWidget(ledButton);

        layout->addLayout(ledLayout);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchSelectedLedButtoIndex(QString)));
    horizontalGroupBox->setLayout(layout);
    horizontalGroupBox->setStyleSheet("QGroupBox{border: 0px solid white;border-radius:1px;background-color: #ffffff;}");
}

void SystemContentWidget::switchSelectedLedButtoIndex(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);

    emit click_Button(current_index);
}

void SystemContentWidget::on_click_Button(int index)
{
    qDebug() << "clicked " << index << endl;
    MxLedIndicator *led = leds.at(index);
    QString ledName = QString(led_name[index]);


    if(led->getState() == true){

        m_mxde->callSetLedBrightness(ledName,0);
        led->setState(false);
    }
    else
    {

         m_mxde->callSetLedBrightness(ledName,1);

        led->setState(true);

    }
}

void SystemContentWidget::onLedBrightnessChanged(const QString &message)
{
    qDebug() << "onLedBrightnessChanged " << message << "\n" << endl;
    int i=0;
    QStringList   strlist = message.split(" ");
    char * name = strdup(strlist.at(0).toLocal8Bit().data());
    int statu = strlist.at(1).toInt();


    for(i = 0; i < m_ledNum; i++)
    {
        if(strcmp(led_name[i],name) == 0)
        {
            break;
        }
    }
    if(i < m_ledNum)
    {
        MxLedIndicator *led = leds.at(i);
        led->setState(statu);
    }
}
void SystemContentWidget::setApplication(QApplication *app)
{
    m_app = app;
}

void SystemContentWidget::setDbusProxy(MxDE *mxde)
{
    m_mxde = mxde;
}

void SystemContentWidget::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}


void SystemContentWidget::initConnection()
{

}

void SystemContentWidget::display()
{

}
