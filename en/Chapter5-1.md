### 5.1 Add runtime library on i.MX6UL series development board 

The Web HMI backend service provided by our company is developed using python. The following Python library needs to be added on the i.MX6UL platform：

```
- backports_abc-0.5.tar.bz2
- certifi-2017.11.5.tar.bz2
- simplejson-3.8.2.tar.bz2
- singledispatch-3.4.0.3.tar.bz2
- pyconnman-0.1.0.tar.bz2
- tornado-4.5.2.tar.bz2
```

The i.MX6UL platform uses yocto to easily add related libraries and build systems. You can view official Python support files at the following URL.
```
http://cgit.openembedded.org/meta-openembedded/tree/meta-python
```
Go to the above URL select recipes-devtools/python, you can see a lot of .bb file, as follows:  

{% raw %}
<div  align="center" >
<img src="/imagech/1-2.png",alt="cover", width=600 >
</div>
<div align="center" > Figure5-1-1 BB files of meta-python </div>
<p></p>
{% endraw %}  


Here we can find the documents we need, the official resources are constantly updated, the names and versions may not be completely consistent, according to the actual situation to choose,The following list is the software version used by our company:  
{% raw %}
<div align="center" > Table 5-1-1 Python Libraries </div>
{% endraw %}  
| Python Library		   |  bb 			|   		path			|
|--------------------------|-----------------------------|--------------------------------------|  
|backports_abc-0.5.tar.bz2 | python-backports-abc_0.4.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|certifi-2017.11.5.tar.bz2 | python-certifi_2018.1.18.bb and python-certifi.inc | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|simplejson-3.8.2.tar.bz2  | python-simplejson_3.8.2.bb |  fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|singledispatch-3.4.0.3.tar.bz2 |python-singledispatch_3.4.0.3.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|tornado-4.5.2.tar.bz2 | python-tornado_4.3.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-devtools/python  |
|pyconnman-0.1.0.tar.bz2 | python-pyconnman_0.1.0.bb | fsl-release-yocto/sources/meta-openembedded/meta-python/recipes-connectivity/python-pyconnman  |
  
We uploaded these configuration files to github for download.
```
https://github.com/hufan/yocto-config-bb/tree/master
```

Some BB configuration files already exist in the yocto source code. If not, you need to download them, after adding the supported bb files, the necessary source code libraries will be downloaded from the official network when the system is built and cross-compiled. To enable these libraries to be cross-compiled and integrated into the file system, modify the corresponding file system bbappend file, execute this event when executing the build system, and add the following in the bb file.    
    


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
    

Our company provides three kinds of file system construction, corresponding bb file is as follows:  

{% raw %}
<div align="center" > Table 5-1-2 i.MX6UL Yocto System Configuration</div>
{% endraw %}  

Filesystem | BB Files |
---- | ---- | ----
core-image-minimal | core-image-minimal.bbappend
core-image-base | core-image-base.bbappend
fsl-image-qt5 | fsl-image-qt5.bbappend

