### 3.1 环境搭建

&emsp;&emsp;本章讲述的MEasy本地HMI的环境包含开发板上的QT5运行环境和ubuntu主机端的的qmake及交叉编译工具链。AM335X和AM437X系列开发板上的QT5运行环境和ubuntu主机端的qmake和交叉编译工具链都是通过buildroot编译出来的，具体请参考下面表格章节进行操作。i.MX6UL系列的QT5运行环境使用yocto编译生成，具体操作参见对应产品的软件开发手册。
{% raw %}
<div align="center" > 表3-1-1 AM335X,AM437X,i.MX6UL系列开发板编译QT </div>
<p></p>
{% endraw %} 
| 开发板 | 文档章节 |
| :--- | :--- |
| MYD-C437X | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  3.4编译QT |
| MYD-C437X-PRU | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  3.4编译QT |
| Rico Board | Rico Board Linux 4.1.18 开发手册.pdf  3.4编译QT |
| MYD-AM335X | MYD-AM335X Linux 4.1.18 开发手册.pdf  3.4编译QT |
| MYD-AM335X-Y | MYD-AM335X-Y Linux 4.1.18 开发手册.pdf  3.4编译QT |
| MYD-AM335X-J | MYD-AM335X-J Linux 4.1.18 开发手册.pdf  3.4编译QT |
| MYD-Y6ULX | MYD-Y6ULX-LinuxDevelopmentGuide_zh  3.3构建文件系统-构建GUI Qt5版的系统|
| MYS-6ULX | MYS-6ULX-LinuxDevelopmentGuide_zh.pdf  3.3构建文件系统-构建GUI Qt5版的系统|
&emsp;&emsp;QT5开发工具QT Creator的安装过程直接参考其文档的章节具体如下表：
{% raw %}
<div align="center" > 表3-1-2 安装QT Creator </div>
<p></p>
{% endraw %} 
| 开发板 | 文档章节 |
| :--- | :--- |
| MYD-C437X | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  5.1安装QT Creator |
| MYD-C437X-PRU | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  5.1安装QT Creator |
| Rico Board | Rico Board Linux 4.1.18 开发手册.pdf  5.1安装QT Creator |
| MYD-AM335X | MYD-AM335X Linux 4.1.18 开发手册.pdf  5.1安装QT Creator |
| MYD-AM335X-Y | MYD-AM335X-Y Linux 4.1.18 开发手册.pdf  5.1安装QT Creator |
| MYD-AM335X-J | MYD-AM335X-J Linux 4.1.18 开发手册.pdf  5.1安装QT Creator |
| MYD-Y6ULX | MYD-Y6ULX-LinuxDevelopmentGuide_zh  5.1安装QT Creator |
| MYS-6ULX | MYS-6ULX-LinuxDevelopmentGuide_zh.pdf  5.1安装QT Creator |
&emsp;&emsp;QT5开发工具QT Creator的配置过程直接参考其文档的章节具体如下表：
{% raw %}
<div align="center" > 表3-1-3  AM335X,AM437X,i.MX6UL系列开发板配置QT Creator </div>
<p></p>
{% endraw %} 
| 开发板 | 文档章节 |
| :--- | :--- |
| MYD-C437X | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  5.2配置QT Creator |
| MYD-C437X-PRU | MYD-AM437X系列 Linux 4.1.18开发手册.pdf  5.2配置QT Creator |
| Rico Board | Rico Board Linux 4.1.18 开发手册.pdf  5.2配置QT Creator |
| MYD-AM335X | MYD-AM335X Linux 4.1.18 开发手册.pdf  5.2配置QT Creator |
| MYD-AM335X-Y | MYD-AM335X-Y 4.1.18 开发手册.pdf  5.2配置QT Creator |
| MYD-AM335X-J | MYD-AM335X-J Linux 4.1.18 开发手册.pdf  5.2配置QT Creator |
| MYD-Y6ULX | MYD-Y6ULX-LinuxDevelopmentGuide_zh  5.2配置QT Creator |
| MYS-6ULX | MYS-6ULX-LinuxDevelopmentGuide_zh.pdf  5.2配置QT Creator |


