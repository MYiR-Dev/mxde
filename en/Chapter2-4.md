### 2.4 CAN BUS

This routine demonstrates how to use CAN bus application to configure the CAN bus, transmit-and-receive data with the CAN interface. For details, refer to the source code of mxcan.

Software Environment**：**

* CAN BUS Application

Hardware Environment**：**

* Two development boards with CAN interface
* Data cable connects the two boards' CAN interface，CANH0&lt;-&gt;CANH0，CANL0&lt;-&gt;CANL0，GND&lt;-&gt;GND

{% raw %}
<div align="center" > Table 2-4-1 Development board CAN interface list </div>
{% endraw %}  

| Board | Interface | Date Cable |
| :--- | :--- | :--- |
| MYD-C437X | J15 CANH0 CANL0 CANH1 CANL1GND | DuPont Line |
| MYD-C437X-PRU | J10 CANH CANL GND | DuPont Line |
| Rico Board | - | - |
| MYD-AM335X | U16 DCAN1 | DuPont Line |
| MYD-AM335X-Y | CON2 DCAN1 | DuPont Line |
| MYD-AM335X-J | J17 DCAN1 | DuPont Line |
| MYD-Y6ULX | J10 PIN3、PIN4| DuPont Line |
| MYS-6ULX  | J13| DuPont Line |
UI Description**：**

{% raw %}
<div  align="center" >
<img src="/imagech/2-4-can.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-4-1 Development board CAN interface test </div>
<p></p>
{% endraw %}  

Setting group box: Set CAN parameters and turn on CAN

Send group box: Send CAN data, including CAN ID and CAN data

Receive group box: introduce CAN data

> Note:   
> 1. Click the edit box in the sending group box to pop up the soft keyboard. After entering the data, you need to click the blue Close button on the soft keyboard to close the soft keyboard. Then click the send button to send the data out. After editing, the edit box is sent. The data in the data is automatically cleared.
>  
> 2. The sending data consists of CAN ID and CAN data: The CAN ID is three digits, such as 001, 011, 111; the CAN data is an array of two digits separated by spaces, for example 01 02 03 04 05 06 07 08.  
>  
> 3. Some type of boards do not support loopback mode.

Test steps:

* Using the DuPont cable to connect the two development board's CAN interface.

* Launch CAN bus applications in MEasy HMI.

* Configure the parameters of the CAN of each development board. The ports may not be the same. The baud rate of the two development boards must be the same.

* After the configuration is complete, click the `Open` button, and then transmit and receive data on the two development boards.



