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

Method：

getLedList   Method of get the name and status of all lights on the board

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| leds | s | get the name and status of all lights | "led1 0 \n led2  0 \n" |

Method：

setLedBrightress  Method of  set the state of the LED

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| led | s | led name | "led1" |
| brightness | i | led status 0 is off 1 is on | 1 |

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| result | i | Successful execution returns 0 | 0 |

Signal：

sigLedBrightnessChanged  Signal of led status has changed

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| message | s | The status and name of the light. | "led1 1" |



