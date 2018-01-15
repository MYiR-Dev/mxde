#!/usr/bin/env python
#coding:utf-8

#

import sys
import time, threading

import tornado.ioloop
import tornado.web
import tornado.options
import tornado.httpserver

from tornado.options import define,options
from tornado.websocket import WebSocketHandler

from application import application

# from traceback import print_exc
# import dbus
# import dbus.decorators
# import dbus.glib
# from gi.repository import GLib

from handler.dbus_mess import mainloop_class
from handler.index import get_ip_address

define("port",default=8090,help="run on th given port",type=int)

def loop_fun():
    n=0
    dbus_call_t = mainloop_class()
    dbus_call_t.mainloop_run()

    while True:
        n = n + 1
        if n>1000:
            n=0
        time.sleep(1)
    print('thread dbus recv evet %s ended.' % threading.current_thread().name)

def main():

    t_thread = threading.Thread(target=loop_fun, name='LoopThread_dbus_signal')
    t_thread.setDaemon(True)
    t_thread.start()

    tornado.options.parse_command_line()
    http_server = tornado.httpserver.HTTPServer(application)
    http_server.listen(options.port)
    ip_addr=get_ip_address("eth0")
    str_temp='Development server is running at http://'+ip_addr+':'+str(options.port)+'/login'
    print (str_temp)
    tornado.ioloop.IOLoop.instance().start()

    # #t.join()
    while 1:
        if not t_thread.isAlive():
            break
        time.sleep(5)
    print ('done')

if __name__ == '__main__':
    main()
