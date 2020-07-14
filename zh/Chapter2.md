## 2. 本地HMI使用介绍

---

&emsp;&emsp;本节主要介绍MEasy 本地HMI中每个APP的使用及使用过程中注意的细节。

**软件环境：**

* u-boot
* linux-4.1.x
* 带QT5运行环境的文件系统
* MEasy 本地HMI V1.0应用程序

&emsp;&emsp;以上软件已经在出厂的时候烧写到对应的开发板里面了。

**硬件环境：**

* MY-TFT070CV2电容屏/HDMI显示屏
* AM437X，AM335X, i.MX6UL系列开发板  

> 默认出厂程序只支持MY-TFT070CV2电容屏，使用HDMI显示屏的用户需要根据开发板手册自行编译适用HDMI的程序。

**硬件连接方式:**

{% raw %}
<div align="center" > 表2-1 开发板显示屏接口 </div>
{% endraw %}  

| 开发板 | LCD接口 |
| :--- | :--- |
| MYD-C437X | J8  LCD\_16bit |
| MYD-C437X-PRU | J20 LCD\_16B |
| Rico Board | J9  LCD |
| MYD-AM335X| J8 LCD |
| MYD-AM335X-Y| J7 LCD |
| MYD-AM335X-J | J8 LCD |
| MYD-Y6ULX | J3 LCD |
| MYS-6ULX | J8 LCD |


