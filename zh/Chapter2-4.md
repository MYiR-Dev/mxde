### 2.4 CAN总线

&emsp;&emsp;本例程演示使用CAN总线应用程序来配置开发板的CAN总线设备及数据收发测试，详情请参考源码mxcan。

**软件环境:**

* CAN总线应用程序

**硬件环境：**

* 带CAN接口的开发板两块
* 数据线连接两块板的CAN接口，CANH0&lt;-&gt;CANH0，CANL0&lt;-&gt;CANL0，GND&lt;-&gt;GND
{% raw %}
<div align="center" > 表2-4-1 开发板CAN接口列表 </div>
{% endraw %}  
| 开发板 | 接口 | 数据线 |
| :--- | :--- | :--- |
| MYD-C437X | J15 CANH0 CANL0 CANH1 CANL1GND | 杜邦线 |
| MYD-C437X-PRU | J10 CANH CANL GND | 杜邦线 |
| Rico Board | 无 | 无 |
| MYD-AM335X | U16 DCAN1 | 杜邦线 |
| MYD-AM335X-Y | CON2 DCAN1 | 杜邦线 |
| MYD-AM335X-J | J17 DCAN1 | 杜邦线 |
| MYD-Y6ULX | J10的PIN3、PIN4| 杜邦线 |
| MYS-6ULX  | J13| 杜邦线 |
**界面介绍：**
{% raw %}
<div  align="center" >
<img src="/imagech/2-4-can.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-4-1 开发板CAN接口测试 </div>
<p></p>
{% endraw %}  

> 注意：   
> 1.发送数据由CAN ID和CAN数据组成：CAN ID数据宽度为三位，例如001、011、111;CAN数据宽度为两位，例如01、11，can数据最大8个字节每个字节间由空格隔开，例如01 02 03 04 05 06 07 08。   
> 2.回环模式部分开发板不支持

**测试步骤：**

* 使用杜邦线连接两块开发板的CAN接口
* 启动各自开发板中的CAN总线应用程序，配置各开发板CAN参数(端口可能会不一样，要保证两块开发板的波特率一致)。
* 配置完成后点击打开按钮，然后在两块开发板进行收发数据测试。    




