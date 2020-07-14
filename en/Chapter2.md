## 2. How to use local HMI

---

This section mainly introduces how to use the applications in MEasy HMI.

Software Environment**：**

* u-boot
* linux-4.1.x
* File system with QT5 operating environment
* MEasy HMI V1.0 application

The above software has been programmed into the corresponding development board.

Hardware Environment**：**

* MY-TFT070CV2 capacitive screen/HDMI display
* AM437X, AM335X i.MX6UL series development board

> The default factory program only supports the MY-TFT070CV2 capacitive screen. Users using the HDMI display need to compile their own HDMI-compatible programs according to the development board manual.

Hardware connection method:

{% raw %}
<div align="center" > Table 2-1 LCD Interface of Development Boards</div>
{% endraw %}  

| Board | LCD Interface |
| :--- | :--- |
| MYD-C437X | J8  LCD\_16bit |
| MYD-C437X-PRU | J20 LCD\_16B |
| Rico Board | J9  LCD |
| MYD-AM335X | J8 LCD |
| MYD-AM335X-Y | J7 LCD |
| MYD-AM335X-J | J8 LCD |
| MYD-Y6ULX | J3 LCD |
| MYS-6ULX | J8 LCD |



