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
#include "homecontentwidget.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QDebug>

HomeContentWidget::HomeContentWidget(QWidget *parent, QObject *obj):BaseWidget(parent,obj)
{
        this->setFixedSize(800, 180);

        //set white background color
        this->setAutoFillBackground(true);
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(Qt::white));
        this->setPalette(palette);
        this->initUI();
        this->initConnection();
//        this->setCurrentLanguage(QString("zh_CN"));
}

void HomeContentWidget::initUI()
{
    QStringList icon_list;
    icon_list<<":/myir/res/myir/sz48.png"<<":/myir/res/myir/bj48.png";
    QStringList text_list;
    text_list << QString("[简体中文]") << QString("[English]") ;
    QHBoxLayout *button_layout = new QHBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
    {
        QPushButton *tool_button = new QPushButton();
        tool_button->setFocusPolicy(Qt::NoFocus);
       // tool_button->setIcon(icon_list.at(i));
        tool_button->setFixedWidth(150);
        tool_button->setText(text_list.at(i));
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        button_layout->addWidget(tool_button);
//        item_list.append(tool_button);

    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));

    QHBoxLayout *layout5 = new QHBoxLayout(this);
//    layout5->addWidget(box_logo);
//    layout5->addLayout(layout4);
    layout5->addLayout(button_layout);
//        layout5->addStretch();
//    layout5->setMargin(10);
//    layout5->setSpacing(50);
    layout5->setContentsMargins(0,0,50,20);



    QVBoxLayout *main_layout = new QVBoxLayout();
//    main_layout->addLayout(layout3);
    main_layout->addLayout(layout5);
    main_layout->setMargin(0);
//    main_layout->setSpacing(50);
//    main_layout->setContentsMargins(10,10,10,10);

    this->setLayout(main_layout);
}

void HomeContentWidget::initConnection()
{

}

void HomeContentWidget::display()
{

}

void HomeContentWidget::setCurrentLanguage(QString &lang)
{

}


void HomeContentWidget::switchPageIndex(QString language)
{
    qDebug() << "switch language: " << language << " \n" <<  endl;
    if(language == "0"){
        emit this->sigLanguageChanged(QString("zh_CN"));
    }
    if(language =="1"){
        emit this->sigLanguageChanged(QString("en"));
    }
}
