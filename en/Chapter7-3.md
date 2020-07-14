### 7.3 RS485

```
                <method name="getRs485List">
                    <arg name="rs485_list" type="s" direction="out"/>
                </method>
```

Method：

getRs485List  Method of get the list of the development board RS485 devices

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| rs485\_list | s | Return the list of RS485 devices on the device, separated by a space. | “/dev/ttyO5  /dev/ttyO6” |

The RS485 configuration interface is the same as the read-write interface and the serial port, but when the setSerialPort method is called, the serial port mode in the passed parameter should be 1 RS485 mode.

