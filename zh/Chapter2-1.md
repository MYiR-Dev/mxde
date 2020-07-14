### 2.1 发光二极管

&emsp;&emsp;本例程演示如何使用MEasy HMI中发光二极管应用来控制开发板上的LED灯，详情请参考源码mxled。

**软件环境：**

* 发光二极管应用程序

**硬件环境：**

* 开发板上面的LED灯

{% raw %}
<div align="center" > 表2-1-1 开发板LED列表 </div>
{% endraw %}  

| 开发板 | LED1 | LED2 | LED3 | LED4 |
| :--- | :--- | :--- | :--- | :--- |
| MYD-C437X | D36  核心板 | D34 底板 | D35 底板 | D36 底板 |
| MYD-C437X-PRU | D36 核心板 | D20 底板 | D19 底板 | D18 底板 |
| Rico Board | D23 | D24 | D25 | D26 |
| MYD-AM335X | D3  核心板 | D40 底板 | D39 底板 | - |
| MYD-AM335X-Y | D3  核心板 | D2 底板 | - | - |
| MYD-AM335X-J | D3  核心板 | D2 底板 | - | - |
| MYD-Y6ULX | D30 | - | - | - | 
| MYS-6ULX  | D13 | D12 | - | - |

**界面说明：**
{% raw %}
<div  align="center" >
<img src="/imagech/2-1-led.jpg",alt="cover", width=480 >
</div>
<div align="center" > 图2-1-1 本地LED测试界面 </div>
<p></p>
{% endraw %}  

&emsp;&emsp;状态栏：指示当前LED灯的状态

&emsp;&emsp;开关栏：控制LED的开关的按钮

&emsp;&emsp;位置栏：说明当前LED在开发板上的丝印位置

**测试步骤：**

&emsp;&emsp;通过操作开关栏对应的按钮来控制对应的LED灯。    
