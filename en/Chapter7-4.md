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

Method：

getCanList   Method of get a list of CAN devices on the development board.

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_list | s | Return the list of CAN devices on the device, separated by a space. | “can0 can1” |

Method：

openCanPort Method of open the CAN device

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_name | s | The name of the CAN device. | “can0” |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN device opened handle. | 4 |

Method：

closeCanPort Method of close CAN device

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN device opened handle. | 4 |
| can\_name | s | The name of the CAN device. | "can0" |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0. | 0 |

Method：

closeCanLoop Method of closing the loop mode of CAN device

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN device opened handle. | 4 |
| can\_name | s | The name of the CAN device. | "can0" |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0. | 0 |

Method：

setCanPort  Method of set up a CAN device

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_name | s | The name of the CAN device. | "can0" |
| bitrate | i | Baud rate. | 115200 |
| status | i | CAN device switch state Open 1 Close 0. | 1 |
| loop | s | Set whether to open loopback  ON OFF. | "OFF" |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Execution returns 0 if the CAN device has been opened and returns 100. Can\_configure is now assigned and parsed. | 0 |
| can\_configure | s | A string consisting of space, separated by a device name, opened handle, baud rate, and loopback mode. | “can0 4 20000 OFF” |

Method：

CanWrite  Method of write data to CAN device

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN device opened handle. | 4 |
| data | s | Data string. | "123456789" |
| size | i | Data length. | 9 |

Return：：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0. | 0 |

Signal：

sigCanRecv Signal of CAN device receive data

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| can\_fd | i | CAN device opened handle. | 4 |
| can\_id | i | The ID of the CAN data frame. | 0x123 |
| can\_dlc | i | The length of the CAN data. | 4 |
| can\_data | s | CAN data. | "0x11 0x22 0x33 0x44" |



