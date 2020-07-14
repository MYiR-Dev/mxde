### 4.5 以太网

&emsp;&emsp;本例程演示使用pyconnman对网卡进行管理。

** 硬件环境：**

&emsp;&emsp;硬件连接参见2.5章节。  

- 在页面可以实时的显示网卡状态，也可以修改设置网卡。
- 修改IP时需要注意，如果修改的是web server使用的网卡，会有提示窗口，点击确认后会修改开发板IP，web 服务断开，开发板重启。

** 注意：**    

&emsp;&emsp;界面中的网卡标签页在有网线连通的时候才会显示，界面显示如下：   
{% raw %}
<div  align="center" >
<img src="/imagech/WEB-NET.png",alt="cover", width=480 >
</div>
<div align="center" > 图4-5-1 Web端以太网测试界面 </div>
<p></p>
{% endraw %}  
