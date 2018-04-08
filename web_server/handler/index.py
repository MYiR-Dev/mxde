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
from handler.connman import ConnmanClient
# from traceback import print_exc
# import dbus.decorators
# import dbus.glib
from handler.dbus_mess import MyClass_json
from handler.dbus_mess import send_message
from handler.dbus_mess import dbus_uart
from handler.dbus_mess import dbus_can
from handler.dbus_mess import dbus_led
from handler.ping import verbose_ping_2
from handler.ping import judge_legal_ip2

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
        self.fd_can_name = "can0"
        self.net_name="net1"

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

# class PageCounter(object):
#     count = 0
#     #led
#     led_statu=0
#     #rs232
#     rs232_baudrate_v = 9600
#     rs232_databit_v = 8
#     rs232_captbit_v = "NONE"
#     rs232_stopbit_v = 1
#     rs232_statu = 0  # close-0 open-1
#     rs232_name = "/dev/tttmxc0"
#     #rs485
#     rs485_baudrate_v = 9600
#     rs485_databit_v = 8
#     rs485_captbit_v = "NONE"
#     rs485_stopbit_v = 1
#     rs485_statu =0   # close-0 open-1
#     rs485_name="/dev/tttmxc0"
#     #can
#     can_baudrate_v = 50000
#     can_buff_send_v = 1000
#     can_statu =0   # close-0 open-1
#     can_name="/dev/tttmxc0"

class Parse_command():

    uart_dbus_call = dbus_uart()
    can_dbus_call = dbus_can()
    led_dbus_call = dbus_led()
    uart_dbus_call.add_signal_call()
    can_dbus_call.add_signal_call()
    led_dbus_call.add_signal_call()

    status_data = MyClass_json()
    status_data.name_cmd = "status_data"

    def serial_rs232_handler(self,python_object,dbus_call_t):
        uart_control = python_object["control"]
        if uart_control == 0:  # close
            # uart_name = python_object["name"]
            dbus_call_t.serial_close(GL.fd_tty232)
            GL.fd_tty232 = 0
        elif uart_control == 1:  # open
            uart_name = python_object["name"]
            GL.fd_tty232 = dbus_call_t.serial_open(uart_name)
            self.status_data.name_status = "RS232_STATUS"
            if GL.fd_tty232>0:
                baudrate = python_object["baud_rate"]
                databit = python_object["databit"]
                stopbit = python_object["stopbit"]
                captbit = python_object["checkbit"]
                dbus_call_t.serial_set_parameter(GL.fd_tty232, baudrate, databit, 0, 1, captbit, stopbit)
                self.status_data.status_operation = "successed"
            else:
                self.status_data.status_operation = "faild"

            self.status_data_data = self.status_data.__dict__
            self.status_json = json.dumps(self.status_data_data)
            send_message(self.status_json, WebSocketHandler_myir)
            # 添加反馈信息到html

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
            self.status_data.name_status = "RS485_STATUS"
            if GL.fd_tty485 > 0:
                baudrate = python_object["baud_rate"]
                databit = python_object["databit"]
                stopbit = python_object["stopbit"]
                captbit = python_object["checkbit"]
                dbus_call_t.serial_set_parameter(GL.fd_tty485, baudrate, databit, 1, 1, captbit, stopbit)
                self.status_data.status_operation = "successed"
            else:
                self.status_data.status_operation = "faild"

            self.status_data_data = self.status_data.__dict__
            self.status_json = json.dumps(self.status_data_data)
            send_message(self.status_json, WebSocketHandler_myir)
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
        GL.fd_can_name =can_name
        can_id = python_object["can_id"]
        can_control = python_object["control"]
        baudrate = python_object["baud_rate"]
        can_loop = python_object["can_loop"]
        # print "can_loop=",can_loop
        if can_control == 0:    # close
            dbus_call_t.can_set_parameter(can_name, baudrate, 0, can_loop)
            dbus_call_t.can_close(can_name, GL.fd_can)
            GL.fd_can = 0
        elif can_control == 1:  # open
            dbus_call_t.can_set_parameter(can_name, baudrate, 1, can_loop)
            GL.fd_can = dbus_call_t.can_open(can_name)  # get can id

            if GL.fd_can>0:
                baudrate = python_object["baud_rate"]
                self.status_data.name_status = "CAN_STATUS"
                # sendbuff_len = python_object["can_len_sendbuff"]
                dbus_call_t.can_set_parameter(can_name, baudrate, 1, can_loop)
                self.status_data.status_operation = "successed"
            else:
                self.status_data.status_operation = "faild"

            self.status_data_data = self.status_data.__dict__
            self.status_json = json.dumps(self.status_data_data)
            send_message(self.status_json, WebSocketHandler_myir)

            # print "uuu=",GL.fd_can
        elif can_control == 2:  # set
            baudrate = python_object["baud_rate"]
            # sendbuff_len = python_object["can_len_sendbuff"]
            dbus_call_t.can_set_parameter(can_name, baudrate, 1, can_loop)
        elif can_control == 3:  # send
            buf_data = python_object["buf_data"]
            can_id = python_object["can_id"]
            buf_send=str(can_id)+"+"+buf_data
            # print "can test=",buf_send
            # print "uuu1=", GL.fd_can
            self.can_dbus_call.can_send_data(GL.fd_can, buf_send, len(buf_data))
        else:
            pass

    def led_handler(self,python_object,dbus_call_t):
        led_name = python_object["name"]
        if led_name=="led_list":
            dbus_call_t.led_list()
        else:
            led_value_set = python_object["value_set"]
            if led_value_set==3:
                return
            dbus_call_t.led_set(led_name,led_value_set)
    def eth_handler(self,python_object):
        eth_op=class_eth()

        eth_name = python_object["name"]
        eth_control=python_object["control"]
        if eth_control==1:   # 设置IP  connman的库有bug，使用
            ip_eth = python_object["dest_addr"]
            ip_netmask = python_object["dest_netmask"]
            ip_gateway = python_object["dest_gateway"]
            str_config = "ifconfig " + eth_name + " "+ip_eth
            os.system(str_config)
            # read and sent to html
            eth_op._eth_handler_to_sent()

        elif eth_control==2:   ## 自动获取ip  
            str_config = "udhcpc -i " + eth_name
            os.system(str_config)
            eth_op._eth_handler_to_sent()
        elif eth_control==3:   ##  ping 测试
            ping_ip=python_object["ping_addr"]
            if judge_legal_ip2(ping_ip):
               for i in range(10):
                ping_log=verbose_ping_2(ping_ip,2)
                eth_data = MyClass_json()
                eth_data.name_cmd = "eth_data"
                eth_data.control="ping"
                eth_data.eth_name=eth_name
                eth_data.ping_data=ping_log
                eth_json_data = eth_data.__dict__
                eth_json = json.dumps(eth_json_data)
                send_message(eth_json, WebSocketHandler_myir)
                
    def update_eth_info(self):
        eth_op = class_eth()
        # eth_op._eth_handler_to_sent()
        # sleep(0.5)
        eth_op._eth_handler_to_sent()

    def update_language(self,python_object):
        
        log = tttm()
        log.log_en()

        # set_language=python_object["set_language"]
        # if set_language=="en":
        #     self.render("index_en.html")
        # elif set_language=="zh":
        #     self.render("index_zh.html")

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
        elif cmd == "eth_cmd":
            self.eth_handler(python_object)
        elif cmd == "eth_cmd_upate":
            self.update_eth_info()
        elif cmd == "language_cmd":
            self.update_language(python_object)

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

def make_string(str):
    return dbus.String(str, variant_level=1)

class WebSocketHandler_myir(tornado.websocket.WebSocketHandler):
    socket_handlers = set()
    mess_t = Parse_command()

    def check_origin(self, origin):
        return True

    def open(self):
        print ("websocket opened")

        WebSocketHandler_myir.socket_handlers.add(self)
        eth_operate = class_eth()
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
        send_message(json_data, WebSocketHandler_myir)

        # config = {'Method': make_string('manual'),
        #           'Address': make_string('192.168.1.108'),
        #           'Netmask': make_string('255.255.255.1')}

        eth_operate._eth_handler_to_sent()
        # sleep(0.5)
        # eth_operate._eth_handler_to_sent()

    def on_message(self, message):
        print '------------------------------------------------------------------------------------------------',message
        self.mess_t.parse_c(message)
        return

    def on_close(self):
        print ('websocket closed')
        # self.mess_t.uart_dbus_call.serial_close(GL.fd_tty485)
        # self.mess_t.uart_dbus_call.serial_close(GL.fd_tty232)
        # self.mess_t.can_dbus_call.can_close(GL.fd_can_name,GL.fd_can)
        WebSocketHandler_myir.socket_handlers.remove(self)

class class_eth():

    def __init__(self):
        self.myConn = ConnmanClient(90)

    def _eth_handler_to_sent(self):
        ##read status and connect
        cnt , list_services_info = self.myConn.get_services_info()
        for i in range(cnt):
            if (list_services_info[i*7+2] == "idle"):
                self.myConn.connect(list_services_info[i*7+1])

        eth_data = MyClass_json()
        eth_data.name_cmd = "eth_data"
        eth_data.control = "data_buff"
        eth_data.eth_number = cnt
        for i in range(cnt):
            eth_data.list_data.append(list_services_info[i * 8 + 3])    #name
            eth_data.list_data.append(list_services_info[i * 8 + 4])    #mac
            eth_data.list_data.append(list_services_info[i * 8 + 5])    #address
            eth_data.list_data.append(list_services_info[i * 8 + 6])    #netmask
            eth_data.list_data.append(list_services_info[i * 8 + 7])    #gateway

        eth_data_json = eth_data.__dict__
        eth_json = json.dumps(eth_data_json)
        # print eth_json
        send_message(eth_json, WebSocketHandler_myir)

    def read_eth_state_and_connect(self):
        cnt , list_services_info = self.myConn.get_services_info()
        for i in range(cnt):
            if (list_services_info[i*7+2] == "idle"):
                self.myConn.connect(list_services_info[i*7+1])

    def _read_eth(self):
        cnt, list_services_info = self.myConn.get_services_info()
        return cnt,list_services_info


class tttm(tornado.web.RequestHandler):
    def log_zh(self):
        temp = str(GL.net_name)
        ip_str = get_ip_address(temp)
        self.render("index_zh.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")
    def log_en(self):
        temp = str(GL.net_name)
        ip_str = get_ip_address(temp)
        self.render("index_en.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")

class login(tornado.web.RequestHandler):
    def get(self):
        # lst = ["myirtech web demo"]
        # self.render("index.html")
        # ip_str = get_ip_address("eth1")
        # self.render("index.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")
        pass
        self.render("login.html")
    def post(self,*args,**kwargs):
        username = self.get_argument('name')
        password = self.get_argument('pwd')

class login_in(tornado.web.RequestHandler):
    def get(self,*args,**kwargs):
        # self.write("login check")
        username = self.get_argument('usermail')
        password = self.get_argument('password')
    def post(self,*args,**kwargs):
        # self.write("welogin check")
        username = self.get_argument('Username')
        password = self.get_argument('Password')
        if username=="admin" and password=='admin':
            temp = str(GL.net_name)
            ip_str = get_ip_address(temp)
            self.render("index_en.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")
        else:
            self.render("login.html")
        # ip_str = get_ip_address("eth1")
        # self.render("index.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")

class language_change(tornado.web.RequestHandler):
    def get(self):
        self.render("login.html")
    def post(self,*args,**kwargs):
        language_read = self.get_argument('language')
        print  language_read
        temp = str(GL.net_name)
        ip_str = get_ip_address(temp)
        if language_read=="zh":
            self.render("index_zh.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")
        else:
            self.render("index_en.html", info_ip=ip_str, info_port_eth=options.port, info_event="myir")

# ajax  method
class AjaxHandler(tornado.web.RequestHandler):
    def post(self):
        global fd_tty
        ret_data=self.get_argument("message")
        ret_data_str = ret_data.encode("utf-8")
        # recv_data = sent_data(fd_tty,ret_data_str,len(ret_data_str))
        # self.write("data recv")
        self.write(str(ret_data))

