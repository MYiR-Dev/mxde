### 7.1 LED

```
                <method name="getLedList">
                    <arg name="leds" type="s" direction="out"/>
                </method>
                <method name="setLedBrightress">
                    <arg name="led" type="s" direction="in"/>
                    <arg name="brightness" type="i" direction="in"/>
                    <arg name="result" type="i" direction="out"/>
                </method>
                <signal name="sigLedBrightnessChanged">
                    <arg name="message" type="s" direction="out"/>
                </signal>
```

方法：

getLedList  获取开发板所有灯的名称和状态的方法

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| leds | s | 返回所有灯的名字和状态。 | "led1 0 \n led2  0 \n" |

方法：

setLedBrightress 设置LED的状态的方法

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| led | s | led名称。 | "led1" |
| brightness | i | led状态 0表示关 1表示开。 | 1 |

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| result | i | 执行成功返回0。 | 0 |

信号：

sigLedBrightnessChanged  led状态改变发送的信号

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| message | s | 灯的状态和名称。 | "led1 1" |



