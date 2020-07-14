## 4 Web HMI使用介绍

---

&emsp;&emsp;本章主要介绍使用Web HMI控制开发板的外围设备，以及使用过程中的注意事项。

**软件环境：**

* u-boot
* linux-4.1.x
* 带Python2, tornado, python-dbus等运行环境的文件系统
* MEasy Web HMI V1.0应用程序

&emsp;&emsp;以上软件已经在出厂的时候烧写到对应的开发板里面了。

**硬件环境：**

* AM437X，AM335X, i.MX6UL系列开发板一块

**注意事项：**  

* 使用前的准备  

&emsp;&emsp;开机之前先搭建好网络环境，开发板任一以太网接口和远端主机位于同一子网。

* web登录方式  

&emsp;&emsp;开发板上电，网络连接成功之后串口会打印Web HMI后端服务绑定的IP地址及端口号，log如下:  
```
Development server is running at http://192.168.1.100:8090/login
```
&emsp;&emsp;在远端主机浏览器中输入: ``` http://192.168.1.100:8090/login ```(此处输入的IP以开发板实际的IP地址为准)进入登录界面。 登录用户名和密码默认都是admin。
{% raw %}
<div  align="center" >
<img src="/imagech/WEB-LOGIN.png",alt="cover", width=480 >
</div>
<div align="center" > 图4 Web HMI 登录界面 </div>
<p></p>
{% endraw %}

* web 语言版本  

&emsp;&emsp;Web HMI提供了中文和英文两种版本（切换语言时会自动关闭以前打开的模块设备）。

* 同步处理  

&emsp;&emsp;本地HMI和Web HMI可以同时打开同一个设备，但是他们操作的是同一个设备句柄，设备的参数一样。如本地HMI先打开RS232设备，Web HMI再打开时则会读取本地HMI设置的参数来使用，反之亦然。开发板RS232、RS485、CAN接到其它设备发来的数据，在本地HMI和Web HMI上可以同时接受数据并显示。
