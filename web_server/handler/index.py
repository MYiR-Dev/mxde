#!/usr/bin/env python
#coding:utf-8

import tornado.websocket  
import tornado.web
import tornado.ioloop
import tornado.httpserver
import tornado.options
import os
import datetime

import socket
import fcntl
import struct
import logging
import time, threading
from time import ctime,sleep
# import simplejson as json
import json

from tornado.web import RequestHandler
from tornado.options import define, options
from tornado.websocket import WebSocketHandler

import traceback
from gi.repository import GLib
import dbus
import dbus.mainloop.glib


# from traceback import print_exc
# import dbus.decorators
# import dbus.glib



from handler.dbus_mess import MyClass_json
from handler.dbus_mess import send_message_to_html

from handler.dbus_mess import dbus_uart
from handler.dbus_mess import dbus_can
from handler.dbus_mess import dbus_led


# import pylibmc
import ctypes
from ctypes import *
import sys
# reload(sys)
# sys.setdefaultencoding('utf-8')

class MyGlobal:
    def __init__(self):
        # self.A = 0
        # self.B = [0]

        self.fd_tty485 = 2
        self.fd_tty232 = 2
        self.fd_can = 2

GL = MyGlobal()

# def get_ip_address(ifname):
#     s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     return socket.inet_ntoa(fcntl.ioctl(
#         s.fileno(),
#         0x8915,  # SIOCGIFADDR
#         struct.pack('256s', ifname[:15])
#     )[20:24])

def get_ip_address(ifname):
  import socket, fcntl, struct
  s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
  inet = fcntl.ioctl(s.fileno(), 0x8915, struct.pack('256s', ifname[:15]))
  ret = socket.inet_ntoa(inet[20:24])
  return ret

##内存数据
class PageCounter(object):
    count = 0

    #led
    led_statu=0

    #rs232
    rs232_baudrate_v = 9600
    rs232_databit_v = 8
    rs232_captbit_v = "NONE"
    rs232_stopbit_v = 1
    rs232_statu = 0  # close-0 open-1
    rs232_name = "/dev/tttmxc0"

    #rs485
    rs485_baudrate_v = 9600
    rs485_databit_v = 8
    rs485_captbit_v = "NONE"
    rs485_stopbit_v = 1
    rs485_statu =0   # close-0 open-1
    rs485_name="/dev/tttmxc0"

    #can
    can_baudrate_v = 50000
    can_buff_send_v = 1000
    can_statu =0   # close-0 open-1
    can_name="/dev/tttmxc0"

class Parse_command():

    uart_dbus_call = dbus_uart()
    can_dbus_call = dbus_can()
    led_dbus_call = dbus_led()

    uart_dbus_call.add_signal_call()
    can_dbus_call.add_signal_call()
    led_dbus_call.add_signal_call()

    def serial_rs232_handler(self,python_object,dbus_call_t):
        uart_control = python_object["control"]
        if uart_control == 0:  # close
            # uart_name = python_object["name"]
            dbus_call_t.serial_close(GL.fd_tty232)
            GL.fd_tty232 = 0
        elif uart_control == 1:  # open
            uart_name = python_object["name"]
            GL.fd_tty232 = dbus_call_t.serial_open(uart_name)
        elif uart_control == 2:  # set
            baudrate = python_object["baud_rate"]
            databit = python_object["databit"]
            stopbit = python_object["stopbit"]
            captbit = python_object["checkbit"]
            dbus_call_t.serial_set_parameter(GL.fd_tty232, baudrate, databit, 0, 1, captbit, stopbit)
        elif uart_control == 3:  # send
            buf_data = python_object["buf_data"]
            dbus_call_t.serial_send_data(GL.fd_tty232, buf_data, len(buf_data))
        else:
            pass

    def serial_rs485_handler(self,python_object,dbus_call_t):
        uart_control = python_object["control"]
        if uart_control == 0:  # close
            # uart_name = python_object["name"]
            dbus_call_t.serial_close(GL.fd_tty485)
            GL.fd_tty485 = 0
        elif uart_control == 1:  # open
            uart_name = python_object["name"]
            GL.fd_tty485 = dbus_call_t.serial_open(uart_name)
        elif uart_control == 2:  # set
            baudrate = python_object["baud_rate"]
            databit = python_object["databit"]
            stopbit = python_object["stopbit"]
            captbit = python_object["checkbit"]
            dbus_call_t.serial_set_parameter(GL.fd_tty485, baudrate, databit, 1, 1, captbit, stopbit)
        elif uart_control == 3:  # send
            buf_data = python_object["buf_data"]
            dbus_call_t.serial_send_data(GL.fd_tty485, buf_data, len(buf_data))
        else:
            pass

    def can_handler(self,python_object,dbus_call_t):
        can_name = python_object["name"]
        can_control = python_object["control"]
        if can_control == 0:  # close
            dbus_call_t.can_close(can_name, GL.fd_can)
            GL.fd_can = 0
        elif can_control == 1:  # open
            GL.fd_can = dbus_call_t.can_open(can_name)
        elif can_control == 2:  # set
            baudrate = python_object["baud_rate"]
            # baudrate_int=int(baudrate)
            sendbuff_len = python_object["can_len_sendbuff"]
            # dbus_call_t.set_serial_parameter(fd_can, baudrate, databit, 0, 1, captbit, stopbit)
            dbus_call_t.can_set_parameter(can_name, baudrate, 1, "ON")
        elif can_control == 3:  # send
            buf_data = python_object["buf_data"]
            self.can_dbus_call.can_send_data(GL.fd_can, buf_data, len(buf_data))
        else:
            pass

    def led_handler(self,python_object,dbus_call_t):
        led_name = python_object["name"]
        if led_name=="led_list":
            dbus_call_t.led_list()
        else:
            led_control = python_object["control"]
            dbus_call_t.led_set(led_name,led_control)

    def parse_c(self,message):
        python_object = json.loads(message)
        cmd = python_object["cmd"]
        if cmd == "uart_cmd":
            self.serial_rs232_handler(python_object,self.uart_dbus_call)
        elif cmd == "uart485_cmd":
            self.serial_rs485_handler(python_object,self.uart_dbus_call)
        elif cmd == "can_cmd":
            self.can_handler(python_object,self.can_dbus_call)
        elif cmd == "led_cmd":
            self.led_handler(python_object,self.led_dbus_call)

        # if cmd=="uart_cmd":
        #     uart_control = python_object["control"]
        #     if uart_control==0:  # close
        #         # uart_name = python_object["name"]
        #         self.uart_dbus_call.serial_close(GL.fd_tty232)
        #         GL.fd_tty232 = 0
        #     elif uart_control==1:  # open
        #         uart_name = python_object["name"]
        #         GL.fd_tty232=self.uart_dbus_call.serial_open(uart_name)
        #     elif uart_control==2:  #set
        #         baudrate = python_object["baud_rate"]
        #         databit = python_object["databit"]
        #         stopbit = python_object["stopbit"]
        #         captbit = python_object["checkbit"]
        #         self.uart_dbus_call.serial_set_parameter(GL.fd_tty232, baudrate, databit, 0, 1, captbit, stopbit)
        #     elif uart_control==3:  #send
        #         buf_data = python_object["buf_data"]
        #         self.uart_dbus_call.serial_send_data(GL.fd_tty232,buf_data,len(buf_data))
        #     else:
        #         pass
        # elif cmd=="uart485_cmd":
        #     uart_control = python_object["control"]
        #     if uart_control == 0:  # close
        #         # uart_name = python_object["name"]
        #         dbus_call_t.serial_close(GL.fd_tty485)
        #         GL.fd_tty485 = 0
        #     elif uart_control == 1:  # open
        #         uart_name = python_object["name"]
        #         GL.fd_tty485 = dbus_call_t.serial_open(uart_name)
        #     elif uart_control == 2:  # set
        #         baudrate = python_object["baud_rate"]
        #         databit = python_object["databit"]
        #         stopbit = python_object["stopbit"]
        #         captbit = python_object["checkbit"]
        #         dbus_call_t.serial_set_parameter(GL.fd_tty485, baudrate, databit, 1, 1, captbit, stopbit)
        #     elif uart_control == 3:  # send
        #         buf_data = python_object["buf_data"]
        #         dbus_call_t.serial_send_data(GL.fd_tty485, buf_data, len(buf_data))
        #     else:
        #         pass
        # elif cmd == "can_cmd":
        #     can_name = python_object["name"]
        #     can_control = python_object["control"]
        #     if can_control == 0:  # close
        #         dbus_call_t.can_close(can_name,GL.fd_can)
        #         GL.fd_can = 0
        #     elif can_control == 1:  # open
        #         GL.fd_can=dbus_call_t.can_open(can_name)
        #     elif can_control == 2:  # set
        #         baudrate = python_object["baud_rate"]
        #         # baudrate_int=int(baudrate)
        #         sendbuff_len = python_object["can_len_sendbuff"]
        #         # dbus_call_t.set_serial_parameter(fd_can, baudrate, databit, 0, 1, captbit, stopbit)
        #         dbus_call_t.can_set_parameter(can_name,baudrate,1,"ON")
        #     elif can_control == 3:  # send
        #         buf_data = python_object["buf_data"]
        #         dbus_call_t.can_send_data(GL.fd_can, buf_data, len(buf_data))
        #     else:
        #         pass
        # elif cmd == "led_cmd":
        #     led_name = python_object["name"]
        #     led_control = python_object["control"]
        #     dbus_call_t.led_set(led_name,led_control)
        #     pass

def read_configure():
    path_file='/etc/board_configure_info.json'
    try:
        file=open(path_file, 'r')
        f_read = json.load(file)
    except:
        print("Did not find the configuration file '/etc/board_configure_info.json' ")

    finally:
        pass

    try:
        rs232_port=f_read['board_info']['rs232_port']
        rs485_port=f_read['board_info']['rs485_port']
        can_port=f_read['board_info']['can_port']
        eth0_port=f_read['board_info']['eth0_port']
    except:
        print ("read error")
        return 0
    return rs232_port,rs485_port,can_port,eth0_port

class read_configure_file():

    def __init__(self):
        pass

    def read_configure(self):
        file = open('board_configure_info.json', 'r')
        f_read = json.load(file)

        try:
            rs232_port=f_read['board_info']['rs232_port']
            rs485_port=f_read['board_info']['rs485_port']
            can_port=f_read['board_info']['can_port']
            eth0_port=f_read['board_info']['eth0_port']
        except:
            print "read error"

        return rs232_port,rs485_port,can_port,eth0_port

class WebSocketHandler_myir(tornado.websocket.WebSocketHandler):
    socket_handlers = set()

    mess_t = Parse_command()

    def check_origin(self, origin):
        return True

    def open(self):
        print ("websocket opened")
        WebSocketHandler_myir.socket_handlers.add(self)

        ## init
        rs232_port, rs485_port, can_port, eth0_port=read_configure()
        configure_data = MyClass_json()
        configure_data.name_cmd="configure_cmd"
        configure_data.rs232_port=rs232_port
        configure_data.rs485_port=rs485_port
        configure_data.can_port=can_port
        configure_data.eth0_port=eth0_port
        configure_data_json = configure_data.__dict__
        json_data = json.dumps(configure_data_json)
        send_message_to_html(json_data, WebSocketHandler_myir)

    def on_message(self, message):
        self.mess_t.parse_c(message)
        return

    def on_close(self):
        print ('websocket closed')
        WebSocketHandler_myir.socket_handlers.remove(self)

class login(tornado.web.RequestHandler):
    def get(self):
        # lst = ["myirtech web demo"]
        # self.render("index.html")
        ip_str = get_ip_address("eth0")
        self.render("index.html", info_ip=ip_str, info_port_eth=options.port, info_event="ws_myir")

        # self.render("test11.html")
    # def post(self,*args,**kwargs):
    #     username = self.get_argument('name')
    #     password = self.get_argument('pwd')
    #     print username

class login_check(tornado.web.RequestHandler):
    def get(self,*args,**kwargs):
        # print("login check")
        # self.write("login check")
        username = self.get_argument('usermail')
        password = self.get_argument('password')
        # print username

    def post(self,*args,**kwargs):
        # print("login check")
        # self.write("welogin check")
        username = self.get_argument('Username')
        password = self.get_argument('Password')
        # print username
        # if username=="admin" and password=='admin':
        #     self.render("home.html")
        #     # self.render("ajax.html")
        # else:
        #     # lst = ["python", "www.itdiffer.com", "qiwsir@gmail.com"]
        #     # self.render("index2.html", info=lst)
        #     self.render("login_err.html",info=lst)

        # self.render("index.html")
        ip_str = get_ip_address("eth0")
        self.render("index.html", info_ip=ip_str, info_port_eth=options.port, info_event="ws_myir")

# ajax  method
class AjaxHandler(tornado.web.RequestHandler):
    def post(self):
        global fd_tty
        ret_data=self.get_argument("message")
        ret_data_str = ret_data.encode("utf-8")
        recv_data = sent_data(fd_tty,ret_data_str,len(ret_data_str))
        # self.write("data recv")
        self.write(str(ret_data))

