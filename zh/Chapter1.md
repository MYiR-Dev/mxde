## 1. MEasy HMI框架介绍

---

&emsp;&emsp;MEasy HMI是深圳市米尔电子有限公司开发的一套人机界面框架，它包含基于QT5的本地HMI和远程的Web HMI。本地HMI需要硬件平台具备显示单元、输入单元、通讯接口、数据存贮单元等；软件部分需要包含dbus、connman和QT5运行时环境等。Web HMI是B/S架构的应用，需要网络接口支持，软件部分包含Python2.x以及tornado, javascript, css, HTML, websocket等运行环境。本地HMI和Web HMI的结构框图如下所示：

{% raw %}
<div  align="center" >
<img src="/imagech/hmi_framework.jpg",alt="cover", width=720 >
</div>

{% endraw%}


{% raw %}
<div align="center" > 图1-1 MEasy HMI结构框图 </div>
<p></p>
{% endraw %}  


&emsp;&emsp;MEasy HMI使用D-Bus作为应用程序和底层硬件的访问接口。RS232、RS485、CAN、LED这些硬件使用米尔提供的一套完整的控制和通信接口，对外提供基于D-BUS的Method和Signal，在最后一章会介绍这些Method和Signal。用户可以根据需要对我们提供的接口进行扩展以实现更强大的功能，关于D-bus的更多细节请参考[http://dbus.freedesktop.org](http://dbus.freedesktop.org)。

&emsp;&emsp;MEasy HMI中的网络管理应用则使用开源的Connman作为中间层来实现对网络设备的控制, Connman也是一个基于D-Bus的完全模块化的系统，可以通过插件化进行扩展，以支持EtherNet、WIFI、3G/4G、Bluetooth等网络设备的管理。关于Connman的更多细节请参考这[https://01.org/zh/node/2207](https://01.org/zh/node/2207)

&emsp;&emsp;MEasy HMI在目标板上目录结构如下，在后面的章节中将会详细介绍MEasy HMI应用如何集成到目标板系统中。  

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