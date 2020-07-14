### 2.3 RS485

&emsp;&emsp;本例程演示如何使用MEasy HMI中的RS485应用来配置开发板的RS485设备及RS485收发数据测试，详情请参考源码mxrs485。

**软件环境:**

* RS485应用程序

**硬件环境：**

* 带RS485接口的开发板两块
* 数据线连接两块板的RS485接口，485A&lt;-&gt;485A，485B&lt;-&gt;485B，GND&lt;-&gt;GND    

{% raw %}
<div align="center" > 表2-3-1 开发板RS485接口列表 </div>
<p></p>
{% endraw %}  
| 开发板 | 接口 | 数据线 |
| :--- | :--- | :--- |
| MYD-C437X | J15  485\_A 485\_B GND | 杜邦线 |
| MYD-C437X-PRU | J10  485A 485B GND | 杜邦线 |
| Rico Board | 无 | 无 |
| MYD-AM335X | U16 UART1 | 杜邦线 |
| MYD-AM335X-Y | CON2 UART2 | 杜邦线 |
| MYD-AM335X-J | J18 UART2 | 杜邦线 |
| MYD-Y6ULX | J10的PIN3、PIN4 |杜邦线 |
| MYS-6ULX  | J9 |杜邦线 |
**界面介绍：**
{% raw %}
<div  align="center" >
<img src="/imagech/2-3-rs485.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-3-1 开发板RS485配置 </div>
<p></p>
{% endraw %}  

> 注意：点击发送组框中的编辑框会弹出软键盘，输入完数据后需要点击软键盘中蓝色Close按钮才能关闭软键盘，然后点击发送按钮才能将数据发送出去，发送完毕后编辑框中的数据自动被清空。

**测试步骤：**

* 使用杜邦线连接两块开发板的RS485接口
* 分别启动各自开发板中的MEasy HMI中的RS485应用程序
* 配置各开发板RS485设置组框的参数，端口可能会不一样，要保证两块开发板的波特率、校验位、数据位和停止位一致。
* 配置完成后点击打开按钮，然后在两块开发板进行收发数据测试。    

 
 



