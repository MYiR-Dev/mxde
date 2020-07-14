### 2.2 Serial

This example shows how to use the serial port application in MEasy HMI to configure the serial port device of the development board and serial port to send and receive data test. For details, please refer to the source code mxserial.

Software Environment**：**

* Serial Application

Hardware Environment**：**

* One MYIR  development board with serial port
* PC with serial assistant software


{% raw %}
<div align="center" > Table 2-2-1 Development board serial list </div>
<p></p>
{% endraw %}  

| Board | Interface | Data Cable |
| :--- | :--- | :--- |
| MYD-C437X | J17 UART3 | DB9 To USB |
| MYD-C437X-PRU | J12 RXD TXD GND | TTL To USB |
| Rico Board | - | - |
| MYD-AM335X | J13 UART2 | DB9 to USB |
| MYD-AM335X-Y | J13 UART1 | TTL to USB |
| MYD-AM335X-J | J12 UART1 | TTL to USB |
| MYD-Y6ULX | J10 PIN9、PIN10 | TTL to USB |
| MYS-6ULX | - | - |

UI Description**：**

{% raw %}
<div  align="center" >
<img src="/imagech/2-2-rs232.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-2-1 Local serial port test UI </div>
<p></p>
{% endraw %}  

Test steps:

* Use a cable to connect the USB port on the PC and the serial port on the development board.

* Open the PC serial port assistant software, set the serial port parameters and open the serial port.

* Open the serial port application in MEasy HMI, set the same serial port parameters as the PC and open the serial port.

* Send data on the PC and the development board respectively, and then see if the data can be received on both sides.



