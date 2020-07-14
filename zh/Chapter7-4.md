### 7.4 CAN

```
                <method name="getCanList">
                    <arg name="can_list" type="s" direction="out"/>
                </method>
                <method name="openCanPort">
                    <arg name="can_name" type="s" direction="in"/>
                    <arg name="can_fd" type="i" direction="out"/>
                </method>
                <method name="closeCanPort">
                    <arg name="can_name" type="s" direction="in"/>
                    <arg name="can_fd" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <method name="closeCanLoop">
                    <arg name="can_name" type="s" direction="in"/>
                    <arg name="can_fd" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <method name="setCanPort">
                    <arg name="can_name" type="s" direction="in"/>
                    <arg name="bitrate" type="i" direction="in"/>
                    <arg name="status" type="i" direction="in"/>
                    <arg name="loop" type="s" direction="in"/>
                    <arg name="ret" type="i" direction="out"/>
                    <arg name="can_configure" type="s" direction="out"/> 
                </method>
                <method name="CanWrite">
                    <arg name="can_fd" type="i" direction="in"/>
                    <arg name="data" type="s" direction="in"/>
                    <arg name="size" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <signal name="sigCanRecv">
                    <arg name="can_fd" type="i" direction="out"/>
                    <arg name="can_id" type="i" direction="out"/>
                    <arg name="can_dlc" type="i" direction="out"/>
                    <arg name="can_data" type="s" direction="out"/>
                </signal>
```

方法：

getCanList 获取开发板上的CAN设备列表的方法

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_list | s | 返回设备上的CAN设备列表，以空格隔开。 | “can0 can1” |

方法：

openCanPort 打开CAN设备的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_name | s | CAN设备的名称。 | “can0” |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN设备打开的句柄。 | 4 |

方法：

closeCanPort 关闭CAN设备的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN设备打开的句柄。 | 4 |
| can\_name | s | CAN设备的名称。 | "can0" |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0。 | 0 |

方法：

closeCanLoop 关闭CAN设备回环模式的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN设备打开的句柄。 | 4 |
| can\_name | s | CAN设备的名称。 | "can0" |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0。 | 0 |

方法：

setCanPort 设置CAN设备的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_name | s | CAN设备的名称。 | "can0" |
| bitrate | i | 波特率。 | 115200 |
| status | i | CAN设备开关状态 打开1 关闭0。 | 1 |
| loop | s | 设置是否打开回环 打开ON 关闭OFF。 | "OFF" |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0，如果CAN设备已被打开返回100，此时can\_configure被赋值了可以解析。 | 0 |
| can\_configure | s | 由设备名、打开的句柄、波特率、回环模式以空格隔开组成的字符串。 | “can0 4 20000 OFF” |

方法：

CanWrite  CAN设备写数据的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN设备打开的句柄。 | 4 |
| data | s | 数据字符串。 | "123456789" |
| size | i | 数据长度。 | 9 |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0。 | 0 |

信号：

sigCanRecv CAN设备收到数据的信号

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN设备打开的句柄。 | 4 |
| can\_id | i | CAN数据帧的ID。 | 0x123 |
| can\_dlc | i | CAN数据的长度。 | 4 |
| can\_data | s | CAN数据。 | "0x11 0x22 0x33 0x44" |



