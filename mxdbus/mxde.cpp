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
#include <QObject>
#include "mxde.h"
#include "mxdbus.h"

MxDE::MxDE(QObject *parent) : QObject(parent)
{
    m_app  = parent;
    m_dbus = MxDbus::getMxDubs(m_app);
}

MxDE::~MxDE()
{
    delete m_app;
    m_app = NULL;
    delete m_dbus;
    m_dbus = NULL;
}

QString MxDE::callGetLedList()
{
    MxDbus *bus = (MxDbus *)m_dbus;
    return bus->getLedList();
}

void MxDE::callSetLedBrightness(QString &led, int brightness)
{
    MxDbus *bus = (MxDbus *)m_dbus;
    bus->setLedBrightness(led, brightness);
}
