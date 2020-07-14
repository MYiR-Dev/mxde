### 2.2 串口

&emsp;&emsp;本例程演示如何使用MEasy HMI中的串口应用来配置开发板的串口设备及串口收发数据测试，详情请参考源码mxserial。

**软件环境:**

* 串口应用程序

**硬件环境：**

* 带UART接口的开发板一块
* 装有串口助手软件的PC 

{% raw %}
<div align="center" > 表2-2-1 开发板串口列表 </div>
<p></p>
{% endraw %}  
| 开发板 | 接口 | 数据线 |
| :--- | :--- | :--- |
| MYD-C437X | J17 UART3 | DB9转USB |
| MYD-C437X-PRU | J12 RXD TXD GND | TTL转USB |
| Rico Board | 无 | 无 |
| MYD-AM335X | J13 UART2 | DB9 |
| MYD-AM335X-Y | J13 UART1 | TTL转USB |
| MYD-AM335X-J | J12 UART1 | TTL转USB |
| MYD-Y6ULX | J10的PIN9、PIN10| TTL转USB |
| MYS-6ULX  | 无 | 无 |

**界面介绍：**
{% raw %}
<div  align="center" >
<img src="/imagech/2-2-rs232.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-2-1 本地串口测试界面 </div>
<p></p>
{% endraw %}  

> 注意：点击发送组框中的编辑框会弹出软键盘，输入完数据后需要点击软键盘中蓝色Close按钮才能关闭软键盘，然后点击发送按钮才能将数据发送出去，发送完毕后编辑框中的数据自动被清空。

**测试步骤：**

* 用连接线连接PC端USB和开发板串口。
* 打开PC端串口助手软件，设置串口参数并打开串口。
* 打开MEasy HMI中串口应用，设置和PC端同样的串口参数并打开串口。
* 分别在PC端和开发板端发送数据，然后看两端能否收到数据。  





