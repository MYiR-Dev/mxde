### 2.5 以太网

&emsp;&emsp;本例程演示如何使用MEasy HMI中的以太网应用来配置开发板的网口及测试网口连通性，详情请参考源码mxnet。

**软件环境:**

* 以太网应用程序

**硬件环境：**

* 可提供DHCP服务的路由器一个

* 带以太网接口的开发板一块
{% raw %}
<div align="center" > 表2-5-1 开发板以太网口列表 </div>
<p></p>
{% endraw %} 
| 开发板 | 接口 |
| :--- | :--- |
| MYD-C437X | J11 EHT1 ， J10 ETH2 |
| MYD-C437X-PRU | J6 ETH1 ，J26 PRU-ETH0 ， J27 PRU-ETH1 |
| Rico Board | J5 ETHERNET |
| MYD-AM335X | J5 ， J6 |
| MYD-AM335X-Y | J5 ，J6 |
| MYD-AM335X-J | J5 ， J6 |
| MYD-Y6ULX | CN2 ETH2 ，CN1 ETH1|
| MYS-6ULX  | CN1 ETH ， CN1 ETH2|
**界面介绍：**
{% raw %}
<div  align="center" >
<img src="/imagech/2-5-net.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-5-1 开发板网口配置 </div>
<p></p>
{% endraw %}  
{% raw %}
<div  align="center" >
<img src="/imagech/2-5-1-net.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-5-2 开发板网口测试 </div>
<p></p>
{% endraw %}  

&emsp;&emsp;标签页：网卡对应的功能页面

&emsp;&emsp;IP信息页面：包含设置组框和信息组框

&emsp;&emsp;Ping测试：测试网络连通性的页面

> 注意：    
> 1.标签页是动态创建的，在没插网线的情况下看不到任何界面的，插入几个网线到网口，就会创建几个标签页，同理拔掉网线会删除对应的标签页。    
> 2.IP获取方式切换到Manual模式下，会弹出IP地址、子网掩码、网关的输入框，可用于手动配置IP。    
> 3.在IP获取方式为Manual模式下，点击IP地址、子网掩码、网关的输入框编辑框会弹出软键盘，输入完数据后需要点击软键盘中蓝色Close按钮才能关闭软键盘，然后点击确定按钮才能将IP地址、子网掩码、网关这些信息配置下去，配置完毕后编辑框中的数据自动被清空。

**测试步骤：**

1.将网线插入开发板的网口。

2.打开MEasy HMI中的以太网测试应用程序，查看信息组框是否成功获取到IP信息。

3.切换到Ping测试页面测试网络联通性。  


