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

#define MXDE_SETTING_FILE_NAME_SETTING  "mxde"
#define MXDE_COMPANY_SETTING            "myirtech"
#define MXDE_SETTING_FILE_PATH          "/usr/share/myir/settings.ini"
class MxApplication : public QtSingleApplication
{
    Q_OBJECT
public:
    MxApplication(int &argc, char **argv, bool GUIenabled = true);

signals:
	void sigLedBrightnessChanged(const QString &message);

public slots:
    void onLedBrightnessChanged(const QString &message);

private:


};

#endif // MXAPPLICATION_H
