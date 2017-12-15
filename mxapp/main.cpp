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
#include "mxmaindialog.h"
#include "mxapplication.h"
#include "mxsplashscreen.h"

#include <QFile>
#include <QTranslator>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    MxApplication app(argc, argv);
    if(app.isRunning()){
        return 0;
    }

    QTranslator translator;

// load qss file

    QFile qss(":/res/qss/mxde.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();


//    MxSplashScreen *splash = new MxSplashScreen(&app);
//    splash->display();

    MxMainDialog w(&app);
    w.setTranslator(&translator);

    w.display();

    return app.exec();
}
