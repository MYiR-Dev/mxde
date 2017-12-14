#include <QObject>
#include <QFile>
#include <QDebug>

#include "mxdesktopfile.h"
#include "mxproperties.h"

MxDesktopFile::MxDesktopFile(const QString &fileName)
{
	
	this->fileName = fileName;
	
	if(!QFile::exists(fileName)){
		return;
	}

	MxProperties desktop(fileName, "Desktop Entry");
    name = desktop.value("Name","").toString();
    name_zh_CN = desktop.value("Name[zh_CN]", "").toString();
	exec = desktop.value("Exec", "").toString();
	tryExec = desktop.value("TryExec", "").toString();
	icon = desktop.value("Icon", "").toString();
	type = desktop.value("Type", "Application").toString();
	categories = desktop.value("Categories").toString().remove(" ").split(";");
	mimeType = desktop.value("MimeType").toString().remove(" ").split(";");

	if(categories.first().compare("") == 0){
		categories.removeFirst();
	}

//    process = new QProcess(this);

    process.setProcessChannelMode(QProcess::ForwardedChannels);

    QObject::connect(&process, SIGNAL(finished(int,QProcess::ExitStatus)),
                      this, SLOT(processFinished(int,QProcess::ExitStatus)));

    QObject::connect(&process, SIGNAL(error(QProcess::ProcessError)),
                      this, SLOT(processError(QProcess::ProcessError)));

    QObject::connect(&process, SIGNAL(started()), this, SLOT(processStarted()));

}

QString MxDesktopFile::getFileName() const
{
	return fileName;
}

QString MxDesktopFile::getPureFileName() const
{
	return fileName.split("/").last().remove(".desktop");
}

QString MxDesktopFile::getName() const
{
	return name;
}

QString MxDesktopFile::getNameCN() const
{
    return name_zh_CN;
}

QString MxDesktopFile::getExec() const
{
	return tryExec.isEmpty()?exec:tryExec;
}

QString MxDesktopFile::getIcon() const
{
	return icon;
}

QString MxDesktopFile::getType() const
{
	return type;
}

QStringList MxDesktopFile::getCategories() const
{
	return categories;
}

QStringList MxDesktopFile::getMimeType() const
{
	return mimeType;
}


void MxDesktopFile::launch()
{
    qDebug() << getExec() << endl;
    process.start(getExec());
}

void MxDesktopFile::processFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    Q_UNUSED(exitCode);
    Q_UNUSED(exitStatus);

    emit demoFinished();

    QObject::disconnect(this, SIGNAL(demoStarted()), 0, 0);
    QObject::disconnect(this, SIGNAL(demoFinished()), 0, 0);
}

void MxDesktopFile::processError(QProcess::ProcessError err)
{
    qDebug() << "Process error: " << err;
    if (err == QProcess::Crashed)
        emit demoFinished();
}


void MxDesktopFile::processStarted()
{
    emit demoStarted();
}
