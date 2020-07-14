### 3.3 Running HMI Applications

This chapter mainly describes the running process of MEasy HMI.

After the compilation is complete, the compiled program can be uploaded to the development board for running. There are two methods for uploading the program to the development board.

Method One: Direct Upload Operation by Configuring Qt Creator

* Configuring Qt Creator remote devices

By selecting the menu bar `Tools->Options->Devices`, select `myir (default for Generic Linux)` in Device, enter the development board IP in the _Type Specific_ field \(you need to log in to the development board through the serial port to view\), user name, and do not need to fill in the password. As shown in Figure 3-3-1.
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-1-device.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-1 Device Configuration  </div>
<p></p>
{% endraw %}  


* Test remote device connectivity

After the input is complete, click the`Apply` button, and then click the `Test`button on the right side will automatically pop up the test connection window when _Device test finished successfully_. The word means the test connection is successful. As shown in Figure 3-3-2.
{% raw %}
<div  align="center" >
<img src="/imagech/3-5-2-test.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-2 Equipment testing </div>
<p></p>
{% endraw %}  


* Specify the program to run

After the test connection is successful, return to the main interface of Qt Creator. To specify the program you want to run, select the program that needs to run as _mxapp_. As shown in Figure 3-3-3.  

{% raw %}
<div  align="center" >
<img src="/imagech/3-5-3.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-3 Select the program to run </div>
<p></p>
{% endraw %}  
* Specify the parameters for the program to run

After specifying the program to be run, you also need to specify the program's operating parameters. Click `Projects->mxde->Build & Run ->myir->Run` to pull down to the Run configuration column and write in the Arguments input box_ --platform linuxfb_, which completes the specification of the program's operating parameters. As shown in Figure 3-3-4.  

{% raw %}
<div  align="center" >
<img src="/imagech/3-5-4.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-4  Program operating parameters </div>
<p></p>
{% endraw %}  
* Kill the running MEasy HMI related program on the development board

After specifying the running parameters, you need to log in to the development board and kill the currently running MEasy HMI related program. The operation is as follows:

`# killall mxbackend`

`# killall mxapp`

* Upload the program to the development board and run

Click the Run button in the lower left corner, or click the menu bar `Build->Run` to upload mxapp to the development board and run it. On the 7-inch screen, you can see the MEasy HMI interface. The running debugging information can be seen in _3 Application Output_, as shown in Figure 3-3-5.



{% raw %}
<div  align="center" >
<img src="/imagech/3-5-5.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-5 Application Output </div>
<p></p>
{% endraw %}  
> Note: If you need to run mxserial mxrs485 mxcan mxled these applications, you need to run mxbackend first, but also need to ensure that these applications and mxbackend connection dbus bus to the same address. The method of operation is as follows:

1.Sets the DBUS\_SESSION\_BUS\_ADDRESS environment variable currently running on the serial terminal.

```
# dbus-launch 
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-qb40GAMAnL,guid=e3ab6092d0c14d9b138e64435ae0b6b0
DBUS_SESSION_BUS_PID=655
# export DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-qb40GAMAnL
```

2.Run the daemon.

```
# cd /home/myir/
# ./mxbackend
```

3.Configure the dbus return bus DBUS\_SESSION\_BUS\_ADDRESS environment variable to run the program in Qt Creator.

Take mxled as an example to illustrate the configuration in Qt Creator. Click on the left `Projects-> mxde-> Build & Run-> myir -> Run -> Run configureation` Select mxled here, in the _Arguments_ input box --platform linuxfb,_ in the Run Enviroment,_ click the Details button, and then click the`Add` button, The _Variable_ column fills in the DBUS\_SESSION\_BUS\_ADDRESS, _Value \_column fills in the value created in the first step dbus-launch above \_unix:abstract=/tmp/dbus-qb40GAMAnL_. As shown in Figure 3-3-6.

{% raw %}
<div  align="center" >
<img src="/imagech/3-5-6.png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-6 Application dbus environment variable configuration </div>
<p></p>
{% endraw %}  
4.Click on the `Run`button in the lower left corner, or click on the menu bar `Build->Run` to upload mxled to the development board and run.

Method two: directly copy the compiled program to the development board

Click the `Projects`button on the left, you can see the project's compilation and configuration. The _Build directory_ in the General column shows the path of the mxde project's compiled output . You can copy the program directly to the development board from here. As shown in Figure 3-3-7.

{% raw %}
<div  align="center" >
<img src="/imagech/3-5-7 .png",alt="cover", width=480 >
</div>
<div align="center" >Figure 3-3-7 Project compilation output </div>
<p></p>
{% endraw %}  


Open the compile output directory, enter the mxapp directory, and copy the mxapp application to the development board. The method of operation is as follows:

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



