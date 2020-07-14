## 4 How to use Web HMI

---

This chapter mainly introduces how to use Web HMI to control the peripherals of the development boards.

** Software Environment：**

* u-boot
* linux-4.1.x
* File system with Python2, tornado, python-dbus and other operating environments 
* MEasy Web HMI V1.0 Application

**Hardwate Environment：**

* Prepare one of the AM437X, AM335X, and i.MX6UL series development boards 

** Note：**  

* Preparation: 

Before starting the system, set up any Ethernet interface on the development board to the same subnet with the remote host.

* Web login 

After the development board is powered on and the network is connected, the serial port will print the IP address and port number bound to the Web HMI backend service. The log is as follows:  
```
Development server is running at http://192.168.1.100:8090/login
```
Open ``` http://192.168.1.100:8090/login ``` (The IP that is filled in here is based on the actual IP address of the development board) in a browser to login, the user name and password are set to `admin` as default.
{% raw %}
<div  align="center" >
<img src="/imagech/WEB-LOGIN.png",alt="cover", width=480 >
</div>
<div align="center" > Figure4-1 Web HMI Login </div>
{% endraw %}

* Web language version 

Web HMI provides Chinese and English versions, the default is English version (switching the language will automatically close the previously opened module device).

* Synchronization  

Local HMI and Web HMI can open the same device at the same time, they operate on the same device handle with the same configuration. If the local HMI opens the RS232 device first, the Web HMI will read the configuration set by the local HMI and vice versa. If the RS232, RS485, CAN receive data from other devices, the data can be accepted and displayed both on the local HMI and Web HMI.


