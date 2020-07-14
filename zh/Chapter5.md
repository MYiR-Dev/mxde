## 5 Web HMI应用开发

---

&emsp;&emsp;Web HMI后端服务是使用python2作为开发语言，基于tornado4.x开发的。i.MX6UL系列开发板使用yocto构建文件系统; AM437X， AM335X系列开发板使用buildroot构建文件系统。它们在构建Web HMI运行时环境上的方式上会存在一些差异，下面将会分别加以说明。

** Web HMI应用目录**

```
├── application.py
├── handler
├── README.md
├── server.py
├── statics
└── template

```

** 启动Web HMI应用**  

&emsp;&emsp;在系统启动过程中加入下面的启动脚本启动Web HMI后端服务，启动Web HMI之前需要先启动DBUS和CONNMAN服务。
```
#!/bin/sh
python /usr/share/myir/init_boardcfg.py &

if test -z "$DBUS_SESSION_BUS_ADDRESS" ; then
        eval `dbus-launch --sh-syntax`
        echo "D-Bus per-session daemon address is: $DBUS_SESSION_BUS_ADDRESS"
fi
export DBUS_SESSION_BUS_ADDRESS="$DBUS_SESSION_BUS_ADDRESS"

/home/myir/mxbackend &
python /usr/share/myir/www/server.py &

TS_CALIBRATION_FILE=/etc/pointercal
if [ ! -f $TS_CALIBRATION_FILE ];then
        export TSLIB_TSDEVICE=/dev/input/touchscreen0
        ts_calibrate
fi
/home/myir/mxapp --platform linuxfb &

```
对于yocto，可以将上面的脚本加入到yocto源码文件 fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir/myir-rc-local/myir-rc-local 中。
	

&emsp;&emsp;程序启动时会读取开发板的配置文件/usr/share/myir/board_cfg.json，配置文件中定义了RS232、RS485、CAN对应的设备文件节点，dbus的参数，系统性信息、led的信息等，修改此配置文件，Web会对应的改变（需重启Web服务）。
```
{
        "board_info": {
                "rs232": [
                        "ttymxc1"
                ],
                "rs485": [
                        "ttymxc3"
                ],
                "can": [
                        "can0"
                ],
                "led": [
                        "myc:blue":"cpu0 - D30  - Core Board"
                ],
                "system": {
                        "HMI_version": "MEasy HMI V1.0",
                        "linux_version": "linux-4.1.15",
                        "uboot_version": "u-boot-2016.03",
                        "gcc_version": "arm-linux-gcc 5.3.0",
                        "manufacturer": "MYIR Tech Limited",
                        "board": "MYD-Y6ULX",
                        "CPU": "i.MX6ULL",
                        "memory": "256MB",
                        "storage": "256MB"
                }
        },

        "dbus_info": {
                "dbus_name": "com.myirtech.mxde",
                "dbus_path": "/com/myirtech/mxde",
                "dbus_interface": "com.myirtech.mxde.MxdeInterface"
        }
}

```
