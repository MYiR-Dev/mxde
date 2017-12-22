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
#include "systemactionwidget.h"
#include "basewidget.h"

#include <QDebug>
#include <QWidget>
#include <QObject>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>

SystemActionWidget::SystemActionWidget(QWidget *parent, QObject *obj):BaseWidget(parent,obj)
{
    this->setFixedSize(800,60);
    this->setAutoFillBackground(true);

    logo_myir_label = new QLabel();
    title_myir_label = new QLabel();
    m_closeButton = new SystemButton();

    this->initUI();
}

void SystemActionWidget::setParentWindow(QWidget *parent)
{
    m_parent = parent;
}

void SystemActionWidget::initUI()
{
    logo_myir_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap(":/res/images/myir/logo_myir.png");
    logo_myir_label->setPixmap(label_pixmap);
//    img_label->setFixedSize(label_pixmap.size());
    logo_myir_label->setFixedSize(QSize(150,30));
    title_myir_label->setObjectName("whiteLabel");
    title_myir_label->setWordWrap(true);//QLabel自动换行
    title_myir_label->setAlignment(Qt::AlignCenter);
    title_myir_label->setText(tr("LED Test"));

    title_myir_label->setMinimumWidth(500);
    title_myir_label->setMaximumWidth(800);
    title_myir_label->setContentsMargins(10,10,0,0);

    m_closeButton->loadPixmap(":/res/images/sys/close_button.png");
    m_closeButton->setFocusPolicy(Qt::NoFocus);

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(logo_myir_label);
    layout1->addStretch();
    layout1->setSpacing(0);
    layout1->setContentsMargins(10, 2, 10, 20);

    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addWidget(m_closeButton);
    layout2->addStretch();
    layout2->setSpacing(0);

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addLayout(layout1);
    layout3->addWidget(title_myir_label);
    layout3->addStretch();
    layout3->addLayout(layout2);
    layout3->setSpacing(0);
    layout3->setContentsMargins(10, 2, 2, 20);
    setLayout(layout3);
}

void SystemActionWidget::initConnection()
{
    connect(m_closeButton, SIGNAL(clicked()), m_parent, SLOT(OnSystemDialogClosed()));
}

void SystemActionWidget::display()
{

}

void SystemActionWidget::setCurrentLanguage(QString &lang)
{
    qDebug() << "BoxActionWidget setCurrentLanguage :" << lang << endl;
}

