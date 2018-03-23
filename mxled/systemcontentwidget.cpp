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
#include "constant.h"
#include "mxapplication.h"

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

SystemContentWidget::SystemContentWidget(QWidget *parent, MxApplication *obj, int width , int height ):BaseWidget(parent,obj)
{
    m_width = width;
    if(m_width <=0){
        m_width = DEFAULT_SCREEN_WIDTH;
    }
    m_height = height;
    if(m_height <= 0){
        m_height = DEFAULT_SCREEN_HEIGHT;
    }

    this->setFixedSize(m_width, m_height);

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


        ledLable = new QLabel();
        ledLable->adjustSize();

        getBoardLedInfo();

        mainLayout->addWidget(horizontalGroupBox,0,0,1,3,Qt::AlignCenter);
        mainLayout->addWidget(ledLable,1,0,2,1);

        setLayout(mainLayout);

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
    QTextStream txtInput(&f);
    txtInput.setCodec(codec);
    QString ledinfoStr;

    ledinfoStr.append( txtInput.readAll());

    ledLable->setStyleSheet("color:#000000;font: 18px");
    ledLable->setText(ledinfoStr);
    f.close();

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
        ledButton->setObjectName("ledButton");
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
void SystemContentWidget::setApplication(MxApplication *app)
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
