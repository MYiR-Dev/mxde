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
#ifndef MXDBUS_H
#define MXDBUS_H

#include <QObject>
#include <QWidget>
#include <QMutex>

#include "mxde_interface.h"

#define DBUS_SERVICE_NAME   "com.myirtech.mxde"
#define DBUS_SERVICE_PATH   "/com/myirtech/mxde"

class MxDbus : public QObject
{
    Q_OBJECT
public:
    static MxDbus *getMxDubs(QObject *object);
    bool    isValid();

    QString getLedList();
    void    setLedBrightness(QString &led, int brightness);
    int openSerialPort(const QString &dev_name);
    void closeSerialPort(int uart_fd);
    void setSerialPort(const QString &parameter);
    QString getSerialList();
    void SerialWrite(int uart_fd, const QString &data, int size);
    QString getRs485List();
signals:

public slots:

protected:
    void startService();
    void stopService();

private:
    explicit MxDbus(QObject *parent = 0);
    ~MxDbus();

//    QReadWriteLock internalMutex;
//    static QMutex  m_mutex;
//    static QAtomicPointer<MxDbus> m_dbus;
    static MxDbus   *m_dbus;
    QObject  *m_object;
    com::myirtech::mxde::MxdeInterface  *mxde_session_iface;
    com::myirtech::mxde::MxdeInterface  *mxde_system_iface;
    bool isvalid;
};

#endif // MXDBUS_H
