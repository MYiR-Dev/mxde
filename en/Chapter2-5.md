### 2.5 Ethernet

This example shows how to use the Ethernet application in the MEasy HMI to configure the development board's network port and test network port connectivity. For details, refer to the source code of mxnet.

Software Environment**：**

* Ethernet Application

Hardware Environment**：**

* One router that can provide DHCP service

* One board with Ethernet interface
{% raw %}
<div align="center" > Table 2-5-1 Development board Ethernet port list </div>
<p></p>
{% endraw %} 

| Board | Interface |
| :--- | :--- |
| MYD-C437X | J11 EHT1 J10 ETH2 |
| MYD-C437X-PRU | J6 ETH1 J26 PRU-ETH0 J27 PRU-ETH1 |
| Rico Board | J5 ETHERNET |
| MYD-AM335X | J5 J6 |
| MYD-AM335X-Y | J5 J6 |
| MYD-AM335X-J | J5 J6 |
| MYD-Y6ULX | CN2 ETH2 CN1 ETH1 |
| MYS-6ULX | CN1 ETH CN1 ETH2 |

UI Description**：**

{% raw %}
<div  align="center" >
<img src="/imagech/2-5-net.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-5-1 Development board network port configuration </div>
<p></p>
{% endraw %}  
{% raw %}
<div  align="center" >
<img src="/imagech/2-5-1-net.jpg",alt="cover", width=480 >
</div>
<div align="center" > Figure 2-5-2 Development board port test </div>
<p></p>
{% endraw %}  


Tab page: Function page corresponding to network card

IP Information Page: Contains settings group box and information group box

Ping Test: Test Network Connectivity Pages

> Note:    
> 1. The application will detect if the Ethernet cable is connected or not. Only when the Ethernet cabled is connected to the Ethernet Jack, the configuration and testing page will show up. The number of Ethernet configurations depends connected Ethernet ports.
>
> 2. When the IP acquisition mode is switched to `Manual` mode, the IP address, subnet mask, and gateway input boxes will pop up, which can be used to configure IP manually.
>
Test steps:

* Insert the network cable into the Ethernet Jack of the development board.

* Open the Ethernet test application in the MEasy HMI and check whether the information group box has successfully obtained the IP information.

* Switch to `Ping test` page to test network connectivity.



