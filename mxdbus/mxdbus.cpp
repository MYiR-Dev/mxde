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
#include "mxdbus.h"

MxDbus::MxDbus(QObject *parent) : QObject(parent)
{
    m_object = parent;
    startService();
}

MxDbus::~MxDbus()
{
    stopService();
    delete m_dbus;
    m_dbus = NULL;
}
MxDbus* MxDbus::m_dbus = NULL;

MxDbus *MxDbus::getMxDubs(QObject *object)
{
        if(m_dbus == NULL){
            m_dbus = new MxDbus(object);
        }
        return m_dbus;
}


void MxDbus::startService()
{
    QDBusConnection session_bus = QDBusConnection::sessionBus();
    mxde_session_iface = new com::myirtech::mxde::MxdeInterface(QString(DBUS_SERVICE_NAME),\
                                                            QString(DBUS_SERVICE_PATH),\
                                                            session_bus,m_object);
    isvalid = mxde_session_iface->isValid();

    if(isvalid){
        connect(mxde_session_iface, SIGNAL(sigLedBrightnessChanged(QString)), \
            m_object, SLOT(onLedBrightnessChanged(QString)));
        connect(mxde_session_iface, SIGNAL(crashed()), m_object, SLOT(on_car_crashed()));

    }
}

bool MxDbus::isValid(){
    return mxde_session_iface->isValid();
}

void MxDbus::stopService()
{
    delete mxde_session_iface;
    mxde_session_iface = NULL;
}

QString MxDbus::getLedList(){
    return mxde_session_iface->getLedList();
}

void    MxDbus::setLedBrightness(QString &led, int brightness)
{
    qDebug() << "setLedBrightness\n" << led << brightness <<  endl;
    mxde_session_iface->setLedBrightress(led,brightness);
}
