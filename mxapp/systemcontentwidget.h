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
#ifndef SYSTEMCONTENTWIDGET_H
#define SYSTEMCONTENTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QList>
#include <QListView>
#include <QModelIndex>

#include "basewidget.h"
#include "mxdesktopfile.h"
#include "mxlistmodel.h"

class SystemContentWidget : public BaseWidget
{
    Q_OBJECT
public:
    SystemContentWidget(QWidget *parent = 0,QObject *obj = 0);

    void setParentWindow(QWidget *w);
    void setCurrentLanguage(QString &lang);
    void initUI();
    void initConnection();
    void display();

    void loadApplications();
    void loadApplicationWidgets();

signals:
    void sigClickSystemInfo();
    void demoFinished();
    void demoStarted();

public slots:
    void OnClickListView(const QModelIndex &index);

private:
    QWidget                 *m_parent_window;
    QLabel                  *m_demo;
    QListView               *m_list_view;
    QList<MxDesktopFile *>   m_apps;
    MxListModel              m_appModel;
};

#endif // SYSTEMCONTENTWIDGET_H
