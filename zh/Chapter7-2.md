### 7.2 串口

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

方法：

openSerialPort 打开串口的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| dev\_name | s | 串口设备的名称 | “/dev/ttyO5” |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | 串口设备打开的句柄。如果串口设备已被打开返回0，此时tty\_configure被赋值了可以解析。 | 4 |
| tty\_configure | s | 由设备名称、打开句柄、波特率、数据位、串口模式、流控、校验位、停止位以空格相隔组成的字符串 | “/dev/ttyO3 4 300 8 0 0 NONE 1” |

方法：

closeSerialPort 关闭串口方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | 打开串口的句柄 | 4 |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0 | 0 |

方法：

setSerialPort 设置串口的配置的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| parameter | s | 串口配置由波特率、数据位、串口模式、流控、校验位、停止位以空格相隔组成的字符串。串口模式0表示RS232  1表示RS485 | “4 115200 8 0 0 78 1” |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0 | 0 |

方法：

getSerialList  获取开发板上的串口设备的方法

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| serial\_list | s | 返回设备上的串口设备列表，以空格隔开 | “/dev/ttyO3  /dev/ttyO4” |

方法：

SerialWrite  串口设备写数据的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | 打开串口的句柄 | 4 |
| data | s | 数据字符串 | "123456789" |
| size | i | 数据长度 | 9 |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0 | 0 |

信号：

sigSerialRecv 串口设备收到数据的信号

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| uart\_fd | i | 串口设备的句柄 | 4 |
| data | s | 串口设备收到的数据 | "123456789" |
| size | i | 数据长度 | 9 |



