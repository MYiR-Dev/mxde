#include "mxmaindialog.h"
#include "mxapplication.h"

#include <QApplication>
#include <QSettings>
#include <QTranslator>

#define MXDE_SETTING_FILE_PATH          "/usr/share/myir/settings.ini"

int main(int argc, char *argv[])
{
    MxApplication app(argc, argv);
    if(app.isRunning()){
        return 0;
    }


//    MxDE        *mxde = new MxDE(&app);

    QTranslator translator;

    QFile qss(":/res/qss/mxde.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    QSettings           *m_Settings = NULL;
    QString             m_current_language="en";

    m_Settings = new QSettings(QString(MXDE_SETTING_FILE_PATH), QSettings::IniFormat);

    m_Settings->beginGroup("LANGUAGE");
    m_current_language = m_Settings->value("language").toString();
    if(m_current_language.isEmpty()){
        m_current_language = "en";
    }
    m_Settings->endGroup();
    m_Settings->sync();

    if(m_current_language == "zh_CN"){
        translator.load(QString(":/res/translation/mxapp_zh_CN.qm"));
    }
    else
    {
        translator.load(QString(":/res/translation/mxapp_en.qm"));
    }

    app.installTranslator(&translator);

    MxMainDialog w(&app);
    w.setApplication(&app);
//    w.setDbusProxy(mxde);


    w.display();
    w.raise();
    w.activateWindow();

    return app.exec();
}
