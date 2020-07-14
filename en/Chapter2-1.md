### 2.1 LED

This example shows how to use the LED application in the MEasy HMI to control the LED on the development board. For details, refer to the source code of mxled.

Software Environment**：**

* LED Application

Hardware Environment**：**

* LED on development board
{% raw %}
<div align="center" > Table 2-1-1 Development board LED list </div>
{% endraw %}  

| Board | LED1 | LED2 | LED3 | LED4 |
| :--- | :--- | :--- | :--- | :--- |
| MYD-C437X | D36  core board | D34 base board | D35 base board | D36 base board |
| MYD-C437X-PRU | D36 core board | D20 base board | D19 base board | D18 base board |
| Rico Board | D23 | D24 | D25 | D26 |
| MYD-AM335X | D3  core board | D40 base board | D39 base board | - |
| MYD-AM335X-Y | D3  core board | D2 base board | - | - |
| MYD-AM335X-J | D3  core board | D2 base board | - | - |
| MYD-Y6ULX | D30 | - | - | - |
| MYS-6ULX | D13 | D12 | - | - |

UI Description**：**

{% raw %}
<div  align="center" >
<img src="/imagech/2-1-led.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-1-1 Local LED test UI </div>
<p></p>
{% endraw %}  

Status bar: indicates the status of current LED.

Switch bar: button to control the switch of current LED.

Position bar: Description of the current silk screen location on the LED redevelopment board.

Test steps:

* The corresponding LED light is controlled by operating the button corresponding to the switch bar.



