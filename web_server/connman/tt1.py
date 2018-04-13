#!/usr/bin/python
##
##  Connman client for wlantest
##
##  Copyright (C) 2012-2013  Aldebaran Robotics. All rights reserved.
##
##  This program is free software; you can redistribute it and/or modify
##  it under the terms of the GNU General Public License version 2 as
##  published by the Free Software Foundation.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
##
CONF_FILE = "/var/lib/connman/connman.config"

import ConfigParser

import dbus
from gi.repository import GLib
import dbus.service
import dbus.mainloop.glib
# import gobject
import pyconnman

class Agent(dbus.service.Object):
    """
    This class is an agent for ConnMan, mostly based on ConnMan simple-agent.
    """
    name = None
    ssid = None
    identity = None
    passphrase = None
    wpspin = None
    username = None
    password = None

    @dbus.service.method("net.connman.Agent",
                         in_signature='', out_signature='')
    def Release(self):
        loop.quit()

    def input_passphrase(self):
        response = {}

        if self.identity:
            response["Identity"] = self.identity
        if self.passphrase:
            response["Passphrase"] = self.passphrase
        if self.wpspin:
            response["WPS"] = self.wpspin

        return response

    def input_username(self):
        response = {}

        if self.username:
            response["Username"] = self.username
        if self.password:
            response["Password"] = self.password

        return response

    def input_hidden(self):
        response = {}

        if self.name:
            response["Name"] = self.name
        if self.ssid:
            response["SSID"] = self.ssid

        return response

    @dbus.service.method("net.connman.Agent",
                         in_signature='oa{sv}', out_signature='a{sv}')
    def RequestInput(self, path, fields):
        response = {}

        if fields.has_key("Name"):
            response.update(self.input_hidden())
        if fields.has_key("Passphrase"):
            response.update(self.input_passphrase())
        if fields.has_key("Username"):
            response.update(self.input_username())

        print response
        return response

    @dbus.service.method("net.connman.Agent",
                         in_signature='', out_signature='')
    def Cancel(self):
        pass


def property_changed(name, value):
    """
    Signal handler for property chaned
    """
    if name == "State":
        val = str(value)
        if val in ('ready', 'online'):
            loop.quit()
            print "Autoconnect callback"


def convert_dbus(obj):
    if (type(obj) is dbus.Byte):
        return int(obj)
    return obj

def make_string(str):
    return dbus.String(str, variant_level=1)

class ConnmanClient:
    """
    Class to get information from ConnMan
    """

    readonly_properties = ['State', 'Error', 'Name', 'Type', 'Security',
                           'Strength', 'Nameservers', 'Timeservers',
                           'Domains', 'IPv4', 'IPv6', 'Ethernet']
    readwrite_properties = ['Autoconnect', 'Nameservers.Configuration',
                            'Timeservers.Configuration', 'Domains.Configuration',
                            'IPv4.Configuration', 'IPv6.Configuration']

    config = {'Method': ' ',
              'Address': ' ',
              'Netmask': ' '}

    def __init__(self, autoconnect_timeout):

        # Setting up bus
        dbus.mainloop.glib.DBusGMainLoop(set_as_default=True)

        self.bus = dbus.SystemBus()
        # self.bus = dbus.SessionBus()
        self.manager = dbus.Interface(self.bus.get_object("net.connman", "/"),
                                      "net.connman.Manager")
        self.technology = dbus.Interface(self.bus.get_object("net.connman",
                # "/"), "net.connman.Services")
                # "/"), "net.connman.Services")
                "/"), "net.connman.Manager")

        # self.manager = pyconnman.ConnManager()

        # agentpath = "/test/agent"
        # self.agent = Agent(self.bus, agentpath)
        # self.manager.RegisterAgent(agentpath)

        # Variables
        self.autoconnect_timeout = autoconnect_timeout
        self.error = None

        # super(ConnmanClient, self).__init__()
        # self.config = dict(self.config ['connman'])

    def handle_connect_error(self, error):
        loop.quit()
        self.error = error
        print "Connect returns an error"

    def handle_connect_reply(self):
        loop.quit()
        self.error = None
        print "Connect callback"

    def autoconnect_timeout_handler(self):
        loop.quit()
        print "Autoconnect timeout"

    def scan(self):
        self.technology.Scan()

    def connect(self, ServiceId, **credentials):
        path = "/net/connman/service/" + ServiceId

        service = dbus.Interface(self.bus.get_object("net.connman", path),
                                 "net.connman.Service")

        if credentials.has_key("name"):
            self.agent.name = credentials["name"]
        if credentials.has_key("passphrase"):
            self.agent.passphrase = credentials["passphrase"]
        if credentials.has_key("identity"):
            self.agent.identity = credentials["identity"]

        service.Connect(timeout=60000,
                        reply_handler=self.handle_connect_reply,
                        error_handler=self.handle_connect_error)

        global loop
        # loop = gobject.MainLoop()
        loop = GLib.MainLoop()
        loop.run()

    def autoconnect(self, ServiceId):
        timeout = GLib.timeout_add(1000 * self.autoconnect_timeout, self.autoconnect_timeout_handler)

        path = "/net/connman/Service/" + ServiceId

        # service = dbus.Interface(self.bus.get_object("net.connman", path),
        #                     "net.connman.Service")

        tech = dbus.Interface(self.bus.get_object('net.connman', path), 'net.connman.Service')

        tech.SetProperty('autoconnect', "yes")
        #
        # service.autoconnect(timeout=60000,
        #                 reply_handler=self.handle_connect_reply,
        #                 error_handler=self.handle_connect_error)

        # signal = self.bus.add_signal_receiver(property_changed,
        #     bus_name="net.connman",
        #     dbus_interface="net.connman.Service",
        #     signal_name="PropertyChanged")
        #
        # global loop
        # loop = GLib.MainLoop()
        # loop.run()
        #
        # GLib.source_remove(timeout)
        # signal.remove()

    def disconnect(self, ServiceId):
        path = "/net/connman/service/" + ServiceId
        service = dbus.Interface(self.bus.get_object("net.connman", path),
                                 "net.connman.Service")
        try:
            service.Disconnect(timeout=60000)
        except dbus.DBusException, error:
            print "%s: %s" % (error._dbus_error_name, error.message)

    def remove(self, ServiceId):
        path = "/net/connman/service/" + ServiceId
        service = dbus.Interface(self.bus.get_object("net.connman", path),
                                 "net.connman.Service")
        try:
            service.Remove()
        except dbus.DBusException, error:
            print "%s: %s" % (error._dbus_error_name, error.message)

    def get_state(self, ServiceId):
        for path, properties in self.manager.GetServices():
            if path == "/net/connman/service/" + ServiceId:
                return properties["State"]

                #    def get_service_id(self, name, technology, security, mac_address):
                #        for path,properties in self.manager.GetServices():
                #            if properties.get("Name") == name and \
                #                    security in properties.get("Security") and \
                #                    properties.get("Ethernet").get('Address') == mac_address:
                #                serviceId = path[path.rfind("/") + 1:]
                #                return serviceId
                #        raise IOError('Service not found !')
                #

    def get_service_id(self, name, technology, security, mac_address):
        for path, properties in self.manager.GetServices():
            # print properties.get("Ethernet").get('Address')
            # print properties.get("IPv4").get('Address')
            serviceId = path[path.rfind("/") + 1:]
            print "s=", serviceId


            #    if properties.get("Name") == name :
            #        print properties.get("Name")

            #    if  properties.get("Type") == technology :
            #        print properties.get("Type")
            #    if security in properties.get("Security") :
            #        print properties.get("Security")

            #    if properties.get("Ethernet").get('Address') == mac_address:
            #        pass
            #    print properties.get("Ethernet").get('Address')

            #    serviceId = path[path.rfind("/") + 1:]
            #    return serviceId
            # raise IOError('Service not found !')

    def set_ipaddress(self, address, netmask, gateway, nameservers):
        pass

    def get_some(self, address, netmask, gateway):
        ip4config = "IPv4"
        technology = self.technology.GetServices()
        # technology = self.technology.GetProperties()
        print 'HUFAN---',technology
        # print technology['State']
        # print technology['OfflineMode']
        # print technology['SessionMode']
        ip_address = {'Method': 'manual', 'Address': address, 'Netmask': netmask}
        if gateway:
            ip_address['Gateway'] = gateway
            self.technology.SetProperty(ip4config, ip_address)
        # self.technology.SetProperty(self.dnsconfig, nameservers)

    def get_connect_error(self):
        error = self.error
        self.error = None
        return error

    def set_config(self, **param):
        config = ConfigParser.RawConfigParser()
        config.optionxform = str
        config.read(CONF_FILE)

        section = "service_" + param['Name']
        config.remove_section(section)
        config.add_section(section)
        config.set(section, "Type", "wifi")
        for item in param:
            if param.has_key(item):
                config.set(section, item, param[item])

        with open(CONF_FILE, 'w') as configfile:
            config.write(configfile)

    def clear_config(self, name):
        config = ConfigParser.RawConfigParser()
        config.read(CONF_FILE)

        section = "service_" + name
        config.remove_section(section)

        with open(CONF_FILE, 'w') as configfile:
            config.write(configfile)

            ### Eum

    def get_connection_state(self):
        """
        Get the global connection state of a system.
        :return: Possible values are "offline", "idle", "ready" and "online".
        :rtype: string
        """
        return self.manager.State

    def _get_service_by_name(self, name):
        """
            Helper to find a service (aka connection) by its name
            and return its ConnService object
        """
        print "----set", name
        for (path, params) in self.manager.get_services():
            print params.get('Name')
            # if (params.get('Name') == name):
            # print "---get=",pyconnman.ConnService(path)
            return pyconnman.ConnService(path)

    def get_connections(self):
        return [params.get('Name') for (_, params) in self.manager.get_services()]

    def connect(self, conn):
        """
        Connect an available connection
        :param conn: Connection name as returned by :class:`get_connections`
        """
        s = self._get_service_by_name(conn)
        if (s is not None):
            s.connect()

    def disconnect(self, conn):
        """
        Disconnect an available connection
        :param conn: Connection name as returned by :class:`get_connections`
        """
        s = self._get_service_by_name(conn)
        if (s is not None):
            s.disconnect()

    def get_connection_properties(self, conn):
        """
        Get available connection properties
        :param conn: Connection name as returned by :class:`get_connections`
        :return: dictionary of properties
        """
        s = self._get_service_by_name(conn)
        if (s is not None):
            ret_props = {}

            props = s.get_property()
            print 'hufan_IPv4=', props["IPv4"]
            print 'hufan_IPv4.Configuration=', props["IPv4.Configuration"]

            for i in props.keys():
                if (i in self.readonly_properties + self.readwrite_properties):
                    ret_props[i] = convert_dbus(props[i])
                if (i in self.readwrite_properties):
                    s.set_property(i, '000')

            return ret_props

    def set_connection_properties(self, conn, set_props):
        """
        Set connection properties
        :param conn: Connection name as returned by :class:`get_connections`
        :param set_props: dictionary of readwrite properties
        """
        s = self._get_service_by_name(conn)
        if (s is not None):
            props = s.get_property()
            for i in props.keys():
                if (i in self.readwrite_properties):
                    s.set_property(i, set_props[i])

    def ff(self):
        print self.get_connection_state()
        # if (self.get_connection_state() == 'ready' and self.config['enabled']):
        if (self.get_connection_state() == 'ready'):
            config = {'Method': make_string('manual'),
                      'Address': '192.168.30.2',
                      'Netmask': '255.255.255.0'}
            # s = self._get_service_by_name(self.config['interface'])
            # if (s is not None):
            ret1 = self.get_connections()
            s = self._get_service_by_name(ret1)
            s.set_property('IPv4', config)
            s.connect()


if (__name__ == "__main__"):
    myConn = ConnmanClient(90)
    # print myConn.get_service_id(None, 'wifi', 'psk', '44:39:c4:2a:f7:38')
    # print myConn.get_service_id(None, 'eth0', 'psk', '4e:19:e0:b0:15:2b')
    myConn.get_service_id(None, 'eth1', 'psk', '4e:19:e0:b0:15:2b')

    print "================================================="
    print "================================================="
    print "================================================="

    # myConn.set_ipaddress('192.168.30.119', '255.255.255.0', '192.168.30.1', 'ethernet_aa64e28454ba_cable')
    # print myConn.get_state('ethernet_aa64e28454ba_cable')
    # print myConn.get_state('ethernet_d60f3c991df5_cable')

    print myConn.get_some('192.168.30.105','255.255.255.0','92.168.30.2')
    # print myConn.autoconnect('ethernet_d60f3c991df5_cable')
    # print myConn.connect('ethernet_d60f3c991df5_cable')

    #
    # # print "tt0="
    # ret1=myConn.get_connections()
    # # print ret1
    # print myConn.get_connection_state()
    # print "tt1="
    # myConn.get_connection_properties(ret1)
    # print " "
    # # myConn.ff()

