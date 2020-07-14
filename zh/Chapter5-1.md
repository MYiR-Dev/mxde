### 5.1  i.MX6UL系列开发板上添加运行时库

&emsp;&emsp;我司提供的Web HMI后端服务是以python开发，在i.MX6UL平台需要添加以下Python库：

```
- backports_abc-0.5.tar.bz2
- certifi-2017.11.5.tar.bz2
- simplejson-3.8.2.tar.bz2
- singledispatch-3.4.0.3.tar.bz2
- pyconnman-0.1.0.tar.bz2
- tornado-4.5.2.tar.bz2
```

&emsp;&emsp;i.MX6UL平台使用yocto可以很方便的添加相关的库并构建系统，在下面的网址，可以查看到官方提供的Python支持文件。
```
http://cgit.openembedded.org/meta-openembedded/tree/meta-python
```
&emsp;&emsp;进入上面的网址中选择recipes-devtools/python，可以看到很多的.bb文件,如下。  

{% raw %}
<div  align="center" >
<img src="/imagech/1-2.png",alt="cover", width=600 >
</div>
<div align="center" > 图5-1-1 meta python内容 </div>
<p></p>
{% endraw %}  


&emsp;&emsp;在此可以找到我们需要的文件，官方的资源在不断更新的，名称和版本可能不是完全一致的，根据实际情况选择,如下列表为我司使用的软件版本: 
{% raw %}
<div align="center" > 表5-1-1 python库列表 </div>
{% endraw %}  
| Python库		   |  bb文件 			|   		存放路径			|
|--------------------------|-----------------------------|--------------------------------------|  
|backports_abc-0.5.tar.bz2 | python-backports-abc_0.4.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|certifi-2017.11.5.tar.bz2 | python-certifi_2018.1.18.bb和python-certifi.inc | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|simplejson-3.8.2.tar.bz2  | python-simplejson_3.8.2.bb |  fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|singledispatch-3.4.0.3.tar.bz2 |python-singledispatch_3.4.0.3.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|tornado-4.5.2.tar.bz2 | python-tornado_4.3.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|pyconnman-0.1.0.tar.bz2 | python-pyconnman_0.1.0.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-connectivity/python-pyconnman  |
  
这些配置文件上传到了github,用户可以自行下载。
```
https://github.com/hufan/yocto-config-bb/tree/master
```
&emsp;&emsp;有的bb配置文件在yocto源码中已经存在，没有的则需要下载，添加支持的bb文件后，在构建系统时就会从官方网络上下载这些需要的库源码，进行交叉编译。要让这些库交叉编译后整合到文件系统，需修改对应的文件系统bbappend文件,在执行构建系统时执行此事件，在bb文件中加入如下内容。   
  
    
    


```
	...
	libxml2 \
	python-lxml \
	python-certifi \
	python-simplejson \
	python-singledispatch \
	python-backports-abc \
	python-pyconnman \
	python-tornado \
	...
	
```   
    

&emsp;&emsp;我司提供了三种文件系统的构建，对应bb文件如下:  

{% raw %}
<div align="center" > 表5-1-2 i.MX6UL yocto系统配置表 </div>
{% endraw %}  

文件系统 | bb文件 |
---- | ---- | ----
core-image-minimal | core-image-minimal.bbappend
core-image-base | core-image-base.bbappend
fsl-image-qt5 | fsl-image-qt5.bbappend

