### 7.2 Serial

```
                <method name="openSerialPort">
                    <arg name= "dev_name" type="s" direction="in"/>
                    <arg name="uart_fd" type="i" direction="out"/>
                    <arg name="tty_configure" type="s" direction="out"/> 
                <method name="closeSerialPort">
                    <arg name="uart_fd" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <method name="setSerialPort">
                    <arg name="parameter" type="s" direction="in"/> 
                    <arg name="result" type="i" direction="out"/>
                </method>
                <method name="getSerialList">
                    <arg name="serial_list" type="s" direction="out"/>
                </method>
                <method name="SerialWrite">
                    <arg name="uart_fd" type="i" direction="in"/>
                    <arg name="data" type="s" direction="in"/>
                    <arg name="size" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <signal name="sigSerialRecv">
                    <arg name="uart_fd" type="i" direction="out"/>
                    <arg name="data" type="s" direction="out"/>
                    <arg name="size" type="i" direction="out"/>
                </signal>
```

Method：

openSerialPort   Method of  open the serial port

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| dev\_name | s | Serial device name | “/dev/ttyO5” |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | Serial device open handle. If the serial device has been opened to return 0, then tty\_configure is assigned to resolve. | 4 |
| tty\_configure | s | A string consisting of a device name, open handle, baud rate, data bits, serial port mode, flow control, check bits, and stop bits separated by spaces | “/dev/ttyO3 4 300 8 0 0 NONE 1” |

Method：

closeSerialPort  Method of close the serial port method

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | Open the handle of the serial port | 4 |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0 | 0 |

Method：

setSerialPort   Method of configuring the configuration of the serial port

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| parameter | s | The serial port is configured with a string consisting of baud rate, data bits, serial port mode, flow control, parity, and stop bits separated by spaces. Serial Mode 0 means RS232 1 means RS485 | “4 115200 8 0 0 78 1” |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0 | 0 |

Method：

getSerialList  Method of obtaining serial device on development board

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| serial\_liast | s | Return a list of serial devices on the device, separated by spaces. | “/dev/ttyO3  /dev/ttyO4” |

Method：

SerialWrite  Method serial device write data

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | Open the handle of the serial port | 4 |
| data | s | Data string | "123456789" |
| size | i | Data length | 9 |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0 | 0 |

Signal：

sigSerialRecv  Signal of serial device receives data 

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | Serial device handle | 4 |
| data | s | Serial device data received | "123456789" |
| size | i | Data length | 9 |



