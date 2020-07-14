### 3.3 运行本地HMI应用

&emsp;&emsp;本章节主要讲述MEasy本地HMI的运行过程。编译完成后可以将编译完成的程序上传至开发板进行运行，这里提供两个方法将程序上传至开发板。

** 方法一：通过配置Qt Creator直接上传运行 **  

* 配置Qt Creator的远程设备

&emsp;&emsp;通过选择菜单栏`Tools`-&gt;`Options`-&gt;`Devices` 在Device中选择`myir (default for Generic Linux)`，在Type Specific栏输入开发板IP（需要通过串口登录到开发板查看）、用户名，不需要填写密码。如图3-3-1所示。
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-1-device.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-1 设备配置  </div>
<p></p>
{% endraw %}  

* 测试远端设备连通性

&emsp;&emsp;输入完毕后点击`Apply`按钮，然后点击右侧`Test`按钮会自动弹出测试连接的窗口当出现Device test finished successfully.字样意味着测试连接成功。如图3-3-2所示。
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-2-test.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-2 设备测试 </div>
<p></p>
{% endraw %}  

* 指定运行的程序

&emsp;&emsp;测试连接成功后，返回到Qt Creator的主界面，要指定你运行的程序，选择需要Run的程序为mxapp。如图3-3-3所示。  
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-3.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-3 选择需要运行的程序 </div>
<p></p>
{% endraw %}  


* 指定程序运行的参数

&emsp;&emsp;指定完需要运行的程序以后，还需要指定程序的运行参数，依次点击左侧`Projects`-&gt;`mxde`-&gt;`Build & Run` -&gt;`myir`-&gt; `Run`下拉到Run配置栏，在Arguments输入框写入_--platform linuxfb,_即完成了程序运行参数的指定。如图3-3-4所示。  
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-4.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-4  程序运行参数 </div>
<p></p>
{% endraw %}  


* 杀掉开发板上正在运行的MEasy HMI相关程序

&emsp;&emsp;指定完运行的参数以后，还需要登录到开发板，杀掉当前运行的MEasy HMI相关程序，操作如下：

`# killall mxbackend`

`# killall mxapp`

* 上传程序到开发板并运行

&emsp;&emsp;点击左下角的运行按钮，或者点击菜单栏`Build`-&gt;`Run`就可以将mxapp上传至开发板并运行。7寸屏幕上可以看到MEasy HMI的界面，运行调试信息可以在`3 Application Output`中看到，如图3-3-5所示。
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-5.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-5 程序输出 </div>
<p></p>
{% endraw %}  


> 注意：如果需要运行mxserial mxrs485 mxcan mxled这些应用程序，需要先运行mxbackend，还需要保证这些应用程序和mxbackend所连接dbus总线为同一个地址。操作方法如下：

1.设置串口终端当前运行的DBUS\_SESSION\_BUS\_ADDRESS环境变量。

```
# dbus-launch 
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-qb40GAMAnL,guid=e3ab6092d0c14d9b138e64435ae0b6b0
DBUS_SESSION_BUS_PID=655
# export DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-qb40GAMAnL
```

2.运行后台程序。

```
# cd /home/myir/
# ./mxbackend
```

3.配置Qt Creator中运行程序的dbus回话总线DBUS\_SESSION\_BUS\_ADDRESS环境变量。

&emsp;&emsp;以mxled为例说明Qt Creator中的配置。点击左侧`Projects`-&gt;`mxde`-&gt;`Build & Run`-&gt; `myir` -&gt; `Run` -&gt; `Run configureation` 这里选择mxled，，在Arguments输入框写入--platform linuxfb，Run Enviroment中点击Details按钮，然后点击Add按钮, Variable栏填写DBUS\_SESSION\_BUS\_ADDRESS，Value栏填写上面第一步dbus-launch创建的值unix:abstract=/tmp/dbus-qb40GAMAnL。如图3-3-6所示。
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-6.png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-6 应用程序dbus环境变量配置 </div>
<p></p>
{% endraw %}  
  
4.点击左下角的运行按钮，或者点击菜单栏`Build`-&gt;`Run`就可以将mxled上传至开发板并运行

** 方法二：直接拷贝编译好的程序到开发板 **  

&emsp;&emsp;点击左侧`Projects`按钮,可以看到工程的编译配置，General栏中Build directory显示的就是mxde工程编译输出的路径，可以从这里直接把程序拷贝到开发板中。如图3-3-7所示。
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-7 .png",alt="cover", width=480 >
</div>
<div align="center" >图3-3-7 工程编译输出 </div>
<p></p>
{% endraw %}  
  
&emsp;&emsp;打开编译输出目录，进入mxapp目录，拷贝mxapp这个应用程序到开发板。运行方法如下：

```
# ./mxapp --platform linuxfb
=== w= 800 h=480
800 300 m_default_action_height
800 60 m_other_action_height
800 180 m_default_content_height
800 420 m_other_content_height
800 480 
Could not parse application stylesheet
800 300  of HomeActionWidget 
libpng warning: iCCP: known incorrect sRGB profile
800 180  of HomeContentWidget 
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: known incorrect sRGB profile
QLayout::addChildLayout: layout "" already has a parent
QWidget::setLayout: Attempting to set QLayout "" on HomeContentWidget "", which already has a layout
QLayout: Attempting to add QLayout "" to HomeContentWidget "", which already has a layout
QWidget::setLayout: Attempting to set QLayout "" on HomeContentWidget "", which already has a layout
800 60  of BOXA 
libpng warning: iCCP: known incorrect sRGB profile
800 420  of BoxContentWidget 
loadApplicationWidgets
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: known incorrect sRGB profile
libpng warning: iCCP: known incorrect sRGB profile
```



