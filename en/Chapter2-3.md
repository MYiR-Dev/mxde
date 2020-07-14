### 2.3 RS485

This routine demonstrates how to use the RS485 application in MEasy HMI to configure the RS485, transmit-and-receive data with RS485. For details, refer to the source code of mxrs485.

Software Environment**：**

* RS485 Application

Hardware Environment**：**

* Two development boards with RS485 interface
* Data cable connects the RS485 interface of two boards，485A&lt;-&gt;485A，485B&lt;-&gt;485B，GND&lt;-&gt;GND.  


{% raw %}
<div align="center" > Table 2-3-1 Development board RS485 interface list </div>
<p></p>
{% endraw %}  

| Board | Interface | Data Cable |
| :--- | :--- | :--- |
| MYD-C437X | J15  485\_A 485\_B GND | DuPont Line |
| MYD-C437X-PRU | J10  485A 485B GND | DuPont Line |
| Rico Board | - | - |
| MYD-AM335X | U16 UART1 | DuPont Line |
| MYD-AM335X-Y | CON2 UART2 | DuPont Line |
| MYD-AM335X-J | J18 UART2 | DuPont Line |
| MYD-Y6ULX | J10 PIN3、PIN4 |DuPont Line |
| MYS-6ULX  | J9 |DuPont Line |

UI Description**：**

{% raw %}
<div  align="center" >
<img src="/imagech/2-3-rs485.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-3-1 Development board RS485 configuration </div>
<p></p>
{% endraw %}  

Test steps:

* Connecting RS485 Interface of Two Development Boards with DuPont Cable

* Start the RS485 applications in the MEasy HMI in their respective development boards

* Configure the RS485 configuration group box parameters of the development board, the port may be different, to ensure that the two development board baud rate, parity, data bits and stop bits are consistent.

* Click the Open button, and then send and receive data on the two development boards.



