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
#ifndef MXAPPLICATION_H
#define MXAPPLICATION_H

#include <QObject>
#include <QWidget>
#include <QtSingleApplication>
#include "mxde.h"

typedef enum{
    CACHE,
    PACAKAGE,
    COOKIES,
    BROWSER,
    TRACE,
    BIGFILE,
} CLEANERTAB;

struct AutoData
{
    QString appPath;
    QString appName;
    QString appComment;
    QString iconName;
    QString appStatus;
};

typedef enum{
    BUTTON_ENTER,
    BUTTON_LEAVE,
    BUTTON_PRESSED,
    BUTTON_DISABLE,
    BUTTON_FIRST,
    BUTTON_SCALED,
}BUTTONSTATUS;

typedef enum{
    HOMEPAGE,
    BOXPAGE,
    SYSTEMPAGE,
    SETTINGPAGE,
    ABOUTPAGE,
}PAGESTATUS;

#define MXDE_SETTING_FILE_NAME_SETTING  "mxde"
#define MXDE_COMPANY_SETTING            "myirtech"
class MxApplication : public QtSingleApplication
{
    Q_OBJECT
public:
    MxApplication(int &argc, char **argv, bool GUIenabled = true);

signals:

public slots:

private:


};

#endif // MXAPPLICATION_H
