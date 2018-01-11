/* -*- Mode: C; tab-width: 4; indent-tabs-mode: t; c-basic-offset: 4 -*- */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * (C) Copyright 2011 Red Hat, Inc.
 */

/*
 * This example shows how to set manual IPv4 addresses to a connection.
 * It uses Qt and D-Bus libraries to do that.
 *
 * Standalone compilation:
 * g++ -Wall `pkg-config --libs --cflags QtCore QtDBus QtNetwork` `pkg-config --cflags libnm` change-ipv4-addresses.cpp -o change-ipv4-addresses
 *
 * You don't need to have NetworkManager devel package installed; you can just
 * grab nm-dbus-interface.h and put it in the path
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtDBus/QDBusConnection>
#include <QtDBus/QDBusInterface>
#include <QtDBus/QDBusMetaType>
#include <QtDBus/QDBusReply>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QDebug>
#include <QtNetwork/QHostAddress>

#include "arpa/inet.h"


# define DBUS_PATH "/"
# define DBUS_CON_SERVICE "net.connman"
# define DBUS_VPN_SERVICE "net.connman.vpn"
# define DBUS_CON_MANAGER "net.connman.Manager"
# define DBUS_VPN_MANAGER "net.connman.vpn.Manager"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (QDBusConnection::systemBus().isConnected() )
    {
        con_manager = new QDBusInterface(DBUS_CON_SERVICE, DBUS_PATH, DBUS_CON_MANAGER, QDBusConnection::systemBus(), this);
        if (! con_manager->isValid() )
        {
            qDebug() << "con_manager dbus service is not valid!";
        }

        getServices();
    }

    setNetPortComboBox();
    getServiceDetails(ui->netPortComboBox->currentIndex());

    objpath = services_list.at(ui->netPortComboBox->currentIndex()).objpath;
    objmap = services_list.at(ui->netPortComboBox->currentIndex()).objmap;
    extractMapData(ipv4map, objmap.value("IPv4.Configuration") );
    sl_ipv4_method << "dhcp" << "manual" << "off";


    ui->methodComBox->addItems(sl_ipv4_method);

    const QString s_ip4 = "(?:25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])";

    // QLineEdits that allow single address
    QRegularExpression rx4("\\s?|^" + s_ip4 + "(?:\\." + s_ip4 + "){3}" + "$");
    QRegularExpressionValidator* lev_4 = new QRegularExpressionValidator(rx4, this);

    ui->addressLineEdit->setValidator(lev_4);
    ui->netmaskLineEdit->setValidator(lev_4);
    ui->gatewayLineEdit->setValidator(lev_4);


    if (! ipv4map.value("Method").toString().isEmpty() ) {
      ui->methodComBox->setCurrentIndex(sl_ipv4_method.indexOf(QRegularExpression(ipv4map.value("Method").toString())) );

      if(ipv4map.value("Method").toString() == "dhcp")
      {
          ui->addressLineEdit->hide();
          ui->netmaskLineEdit->hide();
          ui->gatewayLineEdit->hide();
      }
    }

    connect(ui->methodComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(ipv4Method(int)));
    connect(ui->netPortComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(netPortMethod(int)));
    connect(ui->pushButton_ok, SIGNAL(clicked()), this, SLOT(updateConfiguration()));
    // connect some dbus signals to our slots
    QDBusConnection::systemBus().connect(DBUS_CON_SERVICE, DBUS_PATH, DBUS_CON_MANAGER, "ServicesChanged", this, SLOT(dbsServicesChanged(QList<QVariant>, QList<QDBusObjectPath>, QDBusMessage)));




}
MainWindow::~MainWindow()
{


    delete ui;

}
void MainWindow::netPortMethod(int idx)
{

    if( idx >= 0)
    {
        objpath = services_list.at(idx).objpath;

        objmap  = services_list.at(idx).objmap;

        extractMapData(ipv4map, objmap.value("IPv4.Configuration") );
        ui->methodComBox->setCurrentIndex(sl_ipv4_method.indexOf(ipv4map.value("Method").toString()) );
        getServiceDetails(idx);
    }

}
void MainWindow::ipv4Method(int idx)
{
    // variables
    if (idx == 1 ) { // index 1 is manual

        //qDebug() << "show";
        ui->addressLineEdit->show();
        ui->netmaskLineEdit->show();
        ui->gatewayLineEdit->show();
    }
    else {
        //qDebug() << "hide";
        ui->addressLineEdit->hide();
        ui->netmaskLineEdit->hide();
        ui->gatewayLineEdit->hide();
    }

    return;
}

bool MainWindow::extractMapData(QMap<QString,QVariant>& r_map, const QVariant& r_var)
{
  //  make sure we can convert the QVariant into a QDBusArgument
  if (! r_var.canConvert<QDBusArgument>() ) return false;
  const QDBusArgument qdba =  r_var.value<QDBusArgument>();

  // make sure the QDBusArgument holds a map
  if (qdba.currentType() != QDBusArgument::MapType ) return false;

  // iterate over the QDBusArgument pulling map keys and values out
    r_map.clear();
    qdba.beginMap();

    while ( ! qdba.atEnd() ) {
      QString key;
      QVariant value;
      qdba.beginMapEntry();
      qdba >> key >> value;
      qdba.endMapEntry();
      r_map.insert(key, value);
    } // while

    qdba.endMap();
    return true;
}

QString MainWindow::getDeviceName(const QDBusObjectPath& objpath)
{
  for (int i = 0; i < services_list.size(); ++i) {
    if (services_list.at(i).objpath == objpath) {
      QMap<QString,QVariant> submap;
      if (services_list.at(i).objmap.value("Type").toString() == "ethernet") {
        extractMapData(submap, services_list.at(i).objmap.value("Ethernet") );
        if (submap.value("Interface").toString().isEmpty() )
          return services_list.at(i).objmap.value("Name").toString();
        else
          return QString(services_list.at(i).objmap.value("Name").toString() + " [%1]").arg(submap.value("Interface").toString() );
      } // if type ethernet

      else if ( services_list.at(i).objmap.value("Type").toString() == "wifi" && services_list.at(i).objmap.value("Name").toString().isEmpty() )
        return tr("[Hidden Wifi]");
      else
        return  services_list.at(i).objmap.value("Name").toString();
    } // if objpath matches
  } // for

  return QString();
}

void MainWindow:: setNetPortComboBox()
{
    int newidx = 0;
    QString cursvc = QString();

     //if the combobox has any items in it save the nick name of the service we are viewing

    if (ui->netPortComboBox->count() > 0)
        cursvc = ui->netPortComboBox->currentText();

    // initilize the page2 display widgets
    ui->netPortComboBox->clear();
    ui->label_details_left->clear();
    ui->label_details_right->clear();


    for (int row = 0; row < services_list.size(); ++row) {
      QString ss = getDeviceName(services_list.at(row).objpath);
      ui->netPortComboBox->addItem(ss);
      if (ss== cursvc)
            newidx = row;
    } // services for loop


    ui->netPortComboBox->setCurrentIndex(newidx);


}
bool MainWindow::getArray(QList<arrayElement>& r_list, const QDBusMessage& r_msg )
{
    // make sure r_msg is a QDBusArgument
    if ( ! r_msg.arguments().at(0).canConvert<QDBusArgument>() ) return false;

    // make sure the QDBusArgument holds an array
    const QDBusArgument &qdb_arg = r_msg.arguments().at(0).value<QDBusArgument>();
    if (qdb_arg.currentType() != QDBusArgument::ArrayType ) return false;

    // iterate over the QDBusArgument pulling array elements out and inserting into
    // an arrayElement structure.
    qdb_arg.beginArray();
    r_list.clear();

    while ( ! qdb_arg.atEnd() ) {
        // make sure the argument is a structure type
        if (qdb_arg.currentType() != QDBusArgument::StructureType ) return false;

        arrayElement ael;
        qdb_arg.beginStructure();
        qdb_arg >> ael.objpath >> ael.objmap;
        qdb_arg.endStructure();
        r_list.append (ael);
    } // while
    qdb_arg.endArray();

  return true;
}
void MainWindow::getServices()
{


    QDBusMessage reply = con_manager->call("GetServices");
    if (reply.type() != QDBusMessage::ReplyMessage)
    {
        qDebug() << "GetProperties error!";
        return;
    }

    // call the function to get the map values
    services_list.clear();
    if(getArray(services_list, reply))
    {
        for (int i = 0; i < services_list.size(); ++i) {
          QDBusConnection::systemBus().disconnect(DBUS_CON_SERVICE, services_list.at(i).objpath.path(), "net.connman.Service", "PropertyChanged", this, SLOT(dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage)));
          QDBusConnection::systemBus().connect(DBUS_CON_SERVICE, services_list.at(i).objpath.path(), "net.connman.Service", "PropertyChanged", this, SLOT(dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage)));
        } // for
    }
    // call the function to get the map values

}
void MainWindow::dbsServicePropertyChanged(QString property, QDBusVariant dbvalue, QDBusMessage msg)
{
    QString s_path = msg.path();
    QVariant value = dbvalue.variant();
    QString s_state;

    qDebug() << "dbsServicePropertyChanged";
    // replace the old values with the changed ones.
    for (int i = 0; i < services_list.count(); ++i) {
        if (s_path == services_list.at(i).objpath.path() ) {
            QMap<QString,QVariant> map = services_list.at(i).objmap;
            map.remove(property);
            map.insert(property, value );
            arrayElement ae = {services_list.at(i).objpath, map};
            services_list.replace(i, ae);
            s_state = map.value("State").toString();
            break;
        } // if
    } // for

    // update the widgets
    updateDisplayWidgets();

  return;
}
void MainWindow::dbsServicesChanged(QList<QVariant> vlist, QList<QDBusObjectPath> removed, QDBusMessage msg)
{

     qDebug() << "dbsServicesChanged";
    // process removed services
    if (! removed.isEmpty() ) {
    for (int i = 0; i < services_list.count(); ++i) {
      if (removed.contains(services_list.at(i).objpath) ) {
        QDBusConnection::systemBus().disconnect(DBUS_CON_SERVICE, services_list.at(i).objpath.path(), "net.connman.Service", "PropertyChanged", this, SLOT(dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage)));
        services_list.removeAt(i);
      } // if
     } // for
    } // if we needed to remove something

    // process added or changed servcies
    // Demarshall the raw QDBusMessage instead of vlist as it is easier..
    if (! vlist.isEmpty() ) {
    QList<arrayElement> revised_list;
    if (! getArray(revised_list, msg)) return;

    // merge the existing services_list into the revised_list
    // first find the original element that matches the revised
    for (int i = 0; i < revised_list.size(); ++i) {
      arrayElement revised_element = revised_list.at(i);
      arrayElement original_element = {QDBusObjectPath(), QMap<QString,QVariant>()};
      for (int j = 0; j < services_list.size(); ++j) {
        if (revised_element.objpath == services_list.at(j).objpath) {
          original_element = services_list.at(j);
          break;
        } // if
      } // j for

      // merge the new elementArray into the existing
      if (! original_element.objpath.path().isEmpty()) {
        QMapIterator<QString, QVariant> itr(revised_element.objmap);
        while (itr.hasNext()) {
          itr.next();
          original_element.objmap.insert(itr.key(), itr.value() );
        } // while

        // now insert the element into the revised list
        QDBusConnection::systemBus().disconnect(DBUS_CON_SERVICE, original_element.objpath.path(), "net.connman.Service", "PropertyChanged", this, SLOT(dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage)));
        revised_list.replace(i, original_element);
        QDBusConnection::systemBus().connect(DBUS_CON_SERVICE, revised_element.objpath.path(), "net.connman.Service", "PropertyChanged", this, SLOT(dbsServicePropertyChanged(QString, QDBusVariant, QDBusMessage)));

      } // if original element is not empty
    } // i for

    // now copy the revised list to services_list
    services_list.clear();
    services_list = revised_list;
    } // revised_list not empty

    // update the widgets
    updateDisplayWidgets();

  return;
}
void MainWindow::updateDisplayWidgets()
{

    this->setNetPortComboBox();

    return;
}
void MainWindow::updateConfiguration()
{

    // Some variables
    QString s;
    QStringList sl;
    QList<QVariant> vlist;
    QMap<QString,QVariant> dict;
    QList<QLineEdit*> lep;
    QStringList slp;



    QDBusInterface* iface_serv = new QDBusInterface(DBUS_CON_SERVICE, objpath.path(), "net.connman.Service", QDBusConnection::systemBus(), this);

    // QCheckboxes
    // Only update if changed

    // ipv4
    vlist.clear();
    vlist << "AutoConnect";
    bool setAutoConnect = true;
    vlist << setAutoConnect;
    iface_serv->callWithArgumentList(QDBus::AutoDetect, "SetProperty", vlist);
    // Only update if an entry has changed.
    if ((ui->methodComBox->currentText() != ipv4map.value("Method").toString() )	|
            (ui->addressLineEdit->text() != ipv4map.value("Address").toString() )      	|
            (ui->netmaskLineEdit->text() != ipv4map.value("Netmask").toString() )				|
            (ui->gatewayLineEdit->text() != ipv4map.value("Gateway").toString()) )			{

        vlist.clear();
        lep.clear();
        slp.clear();
        dict.clear();

        if (ui->methodComBox->currentIndex() >= 0) {
            vlist << "IPv4.Configuration";
            dict.insert("Method", sl_ipv4_method.at(ui->methodComBox->currentIndex()) );
            lep << ui->addressLineEdit << ui->netmaskLineEdit << ui->gatewayLineEdit;
            slp << "Address" << "Netmask" << "Gateway";

            for (int i = 0; i < lep.count(); ++i) {
                s = lep.at(i)->text();
                s = s.simplified(); // really should not be needed with the validator
                if (s.isEmpty() ) break;
                dict.insert(slp.at(i), s);
            } // for

            vlist << QVariant::fromValue(QDBusVariant(dict) );
            iface_serv->callWithArgumentList(QDBus::AutoDetect, "SetProperty", vlist);

            ui->addressLineEdit->clear();
            ui->netmaskLineEdit->clear();
            ui->gatewayLineEdit->clear();
        } // if there is a valid index
    } // if ipv4 changed



    // cleanup
    iface_serv->deleteLater();


}
void MainWindow::getServiceDetails(int index)
{
    //  Make sure we were sent a valid index, can happen if the comboBox is
    //  cleared and for whatever reason could not be reseeded with entries.
    if (index < 0 ) return;

    // variables
    bool b_editable = services_list.size() > 0 ? true : false;

    //  Get the QMap associated with the index stored in an arrayElement
    QMap<QString,QVariant> map = services_list.at(index).objmap;

    //  Some of the QVariants in the map are QMaps themselves, create a data structure for them
    QMap<QString,QVariant> submap;



    QString rs =tr("IPv4<br>");
    extractMapData(submap, services_list.at(index).objmap.value("IPv4") );
    rs.append(tr("IP Address Acquisition: %1<br>").arg(submap.value("Method").toString()) );
    if(submap.value("Method").toString() == "dhcp")
    {

        rs.append(tr("IP Address: %1<br>").arg(submap.value("Address").toString()));
        rs.append(tr("IP Netmask: %1<br>").arg(submap.value("Netmask").toString()));
        rs.append(tr("IP Gateway: %1<br>").arg(submap.value("Gateway").toString()));
    }
    if(submap.value("Method").toString() == "manual")
    {

        extractMapData(submap, services_list.at(index).objmap.value("IPv4.Configuration") );
        rs.append(tr("IP Address: %1<br>").arg(submap.value("Address").toString()));
        rs.append(tr("IP Netmask: %1<br>").arg(submap.value("Netmask").toString()));
        rs.append(tr("IP Gateway: %1<br>").arg(submap.value("Gateway").toString()));
    }

    //  write the text to the right display label
    ui->label_details_right->setText(rs);



    rs = tr("Ethernet<br>");
    extractMapData(submap, services_list.at(index).objmap.value("Ethernet") );
    rs.append(tr("Connection Method: %1<br>").arg(submap.value("Method").toString()));
    rs.append(tr("Interface: %1<br>").arg(submap.value("Interface").toString()) );
    rs.append(tr("Device Address: %1<br>").arg(submap.value("Address").toString()) );
    rs.append(tr("MTU: %1<br>").arg(submap.value("MTU").value<quint16>()) );


    //  write the text to the left display label

    ui->label_details_left->setText(rs);
    // enable or disable the editor button
    //ui.pushButton_configuration->setEnabled(b_editable);

    return;
}
