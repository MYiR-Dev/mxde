## 1. Introduction of MEasy HMI Framework

---

MEasy HMI is a set of human-machine interfaces which contains a local HMI based on QT5 and a Web HMI based on Python2 back-end and HTML5 front-end. It runs on development boards with LCD, touch panel, ethernet and so on.  The dependency software includes dbus, connman and QT5 applications, python, tornado and other components.

MEasy HMI block diagram is shown as below：


{% raw %}
<div  align="center" >
<img src="/imagech/hmi_framework.jpg",alt="cover", width=720 >
</div>

{% endraw%}


{% raw %}
<div align="center" > Figure 1-1 MEasy HMI Framework </div>
<p></p>
{% endraw %}  


D-Bus is an advanced inter-process communication mechanism that is provided by the freedesktop.org project and is distributed under the GPL license. The main purpose of D-Bus is to provide communication for processes in the Linux desktop environment, and to pass Linux desktop environment and Linux kernel events as messages to the process.

More details about D-Bus can be found here [https://www.freedesktop.org/wiki/Software/dbus/](https://www.freedesktop.org/wiki/Software/dbus/)

The MEasy HMI uses D-Bus as the access interface for the QT application and the underlying hardware. The MYIR provides a complete set of control and communication interfaces for RS232, RS485, CAN, and LED hardware and encapsulates the interface into a library for external use based on D-BUS Method and Signal \(Chapter 7 describes these methods and Signal\).

Connman is software for managing network devices running on embedded linux devices. Connman is a fully modular system that can be expanded by plugins to support the management of EtherNet, WIFI, 3G/4G, Bluetooth and other network devices. .

For more details on Connman, please refer to [https://01.org/en/node/2207](https://01.org/en/node/2207)

The MEasy HMI uses Connman as the EtherNet access interface to manage EtherNet by calling the D-bus based Method and Signal provided by the connman service \(Chapter 7 introduces these methods and signals\).  

The directory structure of MEasy HMI is shown on target boards as below. They will be introduced in the following sections in detail.

```
/
├── home
│   └── myir
│       ├── mxapp
│       ├── mxbackend
│       ├── mxcan
│       ├── mxinfo
│       ├── mxled
│       ├── mxnet
│       ├── mxrs485
│       ├── mxserial
│       ├── mxsupport
│       └── mxtaskmanager
└── usr
    ├── bin
    │   ├── psplash
    │   └── psplash-write
    ├── lib
    │   ├── fonts
    │   │   └── msyh.ttc
    │   ├── girepository-1.0
    │   ├── gobject-introspection
    │   ├── libgirepository-1.0.la
    │   ├── libgirepository-1.0.so
    │   ├── libgirepository-1.0.so.1
    │   ├── libgirepository-1.0.so.1.0.0
    │   └── python2.7
    └── share
        ├── applications
        ├── myir
        │   ├── mxde.xml
        │   ├── settings.ini
        │   ├── board_cfg.json
        │   └── www
        │       ├── application.py
        │       ├── handler
        │       ├── README.md
        │       ├── server.py
        │       ├── statics
        │       └── template
        └── pixmaps
```

