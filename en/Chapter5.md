## 5 Web HMI Application Development 

---

&emsp;&emsp;The Web HMI back-end service uses python2 as a development language and was developed based on tornado4.x. i.MX6UL series development board uses yocto to build the file system; AM437X, AM335X series development board uses buildroot to build the file system. They are building a Web HMI runtime environment,There will be some differences in the methods, which will be explained separately below.

** Web HMI Application Directory**

```
├── application.py
├── handler
├── README.md
├── server.py
├── statics
└── template

```

** Web HMI Application **  

&emsp;&emsp; Start the Web HMI backend service by adding the following startup script during system startup. You need to start the DBUS and CONNMAN services before starting the Web HMI.
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
For yocto, add the above script to the yocto source file fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir/myir-rc-local/myir-rc-local.

&emsp;&emsp; When the application starts, it will read the development board configuration file /usr/share/myir/board_cfg.json. The configuration file defines RS232, RS485, CAN corresponding device file nodes, dbus parameters, system information, led information, etc. , modify this configuration file, the Web will correspond to the changes (need to restart the Web service).

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
