
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
#include "boxcontentwidget.h"
#include "mxmaindialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSignalMapper>
#include <QDirIterator>
#include <QStringList>
#include <QPalette>
#include <QDebug>

BoxContentWidget::BoxContentWidget(QWidget *parent, QObject *obj):BaseWidget(parent,obj)
{
        this->setFixedSize(800, 420);
        //set white background color
       this->setAutoFillBackground(true);
        QPalette palette;
        palette.setBrush(QPalette::Window, QBrush(Qt::green));
        this->setPalette(palette);
        this->setStyleSheet("QWidget{border: none;}");

        m_list_view = new QListView(this);
        m_list_view->setFocusPolicy(Qt::NoFocus);
        m_list_view->setAutoFillBackground(true);
        m_list_view->setIconSize(QSize(128, 128));
        m_list_view->setResizeMode(QListView::Adjust);
        m_list_view->setModel(&m_appModel);
        m_list_view->setViewMode(QListView::IconMode);
        m_list_view->setWordWrap(true);
        m_list_view->setFlow(QListView::LeftToRight);
    //    list_view->setMovement(QListView::Static);
        m_list_view->setSpacing(26);
    //    list_view->setLineWidth(110);
        m_list_view->setGeometry(rect());
        this->loadApplications();
        this->loadApplicationWidgets();

        connect(m_list_view,SIGNAL(clicked(const QModelIndex&)),this,SLOT(OnClickListView(const QModelIndex &)));

//        QGridLayout *layout = new QGridLayout(this);
//        layout->addWidget(m_list_view,0,0);
//        layout->setSpacing(0);
//        layout->setMargin(0);
//        layout->setContentsMargins(0, 0, 0, 0);
//        setLayout(layout);

        this->initUI();
}

void BoxContentWidget::initUI()
{

}

void BoxContentWidget::initConnection()
{
    connect(this, SIGNAL(sigClickSystemInfo()), m_parent_window, SLOT(OnSystemInfoClicked()));
}

void BoxContentWidget::display()
{

}

void BoxContentWidget::setParentWindow(QWidget *w)
{
    m_parent_window = w;
}

void BoxContentWidget::setCurrentLanguage(QString &lang)
{
    qDebug() << "setLanguage: " << lang << "\n" << endl;
    QModelIndex qindex = m_appModel.index(0,0,QModelIndex());
    m_appModel.setData(qindex, tr(QT_TRANSLATE_NOOP("BoxContentWidget","System Information")));
    m_appModel.setData(qindex,QIcon(QString("/usr/share/pixmaps/system192.png")),Qt::DecorationRole);

    for(int i=0; i< m_apps.size(); i++){

        qindex = m_appModel.index(i+1, 0, QModelIndex());
        m_appModel.setData(qindex,QIcon(m_apps.at(i)->getIcon()), Qt::DecorationRole);
        if(lang == "zh_CN"){
            m_appModel.setData(qindex,m_apps.at(i)->getNameCN());
        }
        else
        {
            m_appModel.setData(qindex,m_apps.at(i)->getName());
        }

    }
}

void BoxContentWidget::loadApplications()
{
    QDirIterator it("/usr/share/applications", QStringList("*.desktop"),
        QDir::Files | QDir::NoDotAndDotDot, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            it.next();
            m_apps.append(new MxDesktopFile(it.filePath()));
        }
}

void BoxContentWidget::loadApplicationWidgets()
{
    QStringList title;
    qDebug() << "loadApplicationWidgets\n" << endl;
    title << tr("");
    m_appModel.setTitle(title);

    m_appModel.insertRows(0,1,QModelIndex());
    QModelIndex qindex = m_appModel.index(0,0,QModelIndex());

    m_appModel.setData(qindex, tr(QT_TRANSLATE_NOOP("BoxContentWidget","System Information")));
    m_appModel.setData(qindex,QIcon(QString("/usr/share/pixmaps/system192.png")),Qt::DecorationRole);

    for(int i=0; i< m_apps.size(); i++){

        m_appModel.insertRows(i+1, 1, QModelIndex());
        qindex = m_appModel.index(i+1, 0, QModelIndex());
        m_appModel.setData(qindex,QIcon(m_apps.at(i)->getIcon()), Qt::DecorationRole);
        m_appModel.setData(qindex,m_apps.at(i)->getName());
    }


}

void BoxContentWidget::OnClickListView(const QModelIndex & index)
{
    qDebug() << "click row "<< index.row() << endl;
    if(index.row() == 0)
    {
        emit this->sigClickSystemInfo();
    }
    else
    {
       int i = index.row();
       MxDesktopFile *app = m_apps.at(i-1);

       QObject::connect(app, SIGNAL(demoFinished()), this, SIGNAL(demoFinished()));
       QObject::connect(app, SIGNAL(demoStarted()), this, SIGNAL(demoStarted()));

       app->launch();
    }
}
