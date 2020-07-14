### 7.3 RS485

```
                <method name="getRs485List">
                    <arg name="rs485_list" type="s" direction="out"/>
                </method>
```

方法：

getRs485List 获取开发板RS485设备列表的方法

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| rs485\_list | s | 返回设备上的RS485设备列表，以空格隔开。 | “/dev/ttyO5  /dev/ttyO6” |

RS485配置接口和读写接口和串口的一致，只是在调用setSerialPort 这个方法的时候，传递的参数里面的串口模式应为1 RS485模式。

