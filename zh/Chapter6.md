## 6 MEasy HMI应用集成  

---

&emsp;&emsp;在前面的章节中我们介绍了MEasy HMI在目标板上的目录结构，以及本地HMI和Web HMI的运行时环境，开发过程。本章将重点介绍如何将MEasy HMI应用集成到目标板系统当中，使之开机就能启动。


### 6.1 i.MX6UL系列开发板上集成MEasy HMI应用   
 
&emsp;&emsp;Yocto中一个软件包是放在bb文件里的，然后非常多的bb文件集成一个recipe，然后很多的recipe又组成一个meta layer。因此，要加入一个软件包可以在recipe以下加入一个bb（bitbake配置文件）。下面介绍在系统中加入web-demo,
在目录fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir下建立如下目录结构：

```
│
└── web-demo
    └── web-demo.bb

```

&emsp;&emsp;web-demo.bb是对应执行的任务，主要工作是编译代码然后整合软件到rootfs，以shell为开发语言。  

&emsp;&emsp;web-demo.bb的内容如下：
```
DESCRIPTION = "web demo"
DEPENDS = "zlib glibc ncurses "
SECTION = "libs"
LICENSE = "MIT"
PV = "3"
PR = "r0"

PACKAGES = "${PN}-dbg ${PN} ${PN}-doc ${PN}-dev ${PN}-staticdev ${PN}-locale"
PACKAGES_DYNAMIC = "${PN}-locale-*"

SRCREV = "9b0038497d884db1e11046a8fbc8b219bcd6699c"
SRC_URI = "git://github.com/hufan/web-demo-bb;protocol=https;branch=web_server"
LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"
S = "${WORKDIR}/git"
do_compile () {
 tar xvf cJSON.tar.bz2 
 make
}

do_install () {
      install -d ${D}/usr/share/myir/
      install -d ${D}/usr/share/myir/www/
      install -d ${D}/lib/
      install -d ${D}/usr/bin/
      	  
      cp -S ${S}/*.so* ${D}/lib/
      cp -r ${S}/web_server/* ${D}/usr/share/myir/www/

      if [ ${MACHINE} = "myd-y6ul14x14" ]
      then
      install -m 0755 ${S}/board_cfg_mydy6ul.json ${D}/usr/share/myir/board_cfg.json
      elif [ ${MACHINE} = "myd-y6ull14x14" ]
      then
      install -m 0755 ${S}/board_cfg_mydy6ull.json ${D}/usr/share/myir/board_cfg.json
      elif [ ${MACHINE} = "mys6ul14x14" ]
      then
      install -m 0755 ${S}/board_cfg_mysy6ul.json ${D}/usr/share/myir/board_cfg.json
      elif [ ${MACHINE} = "mys6ull14x14" ]
      then
      install -m 0755 ${S}/board_cfg_mysy6ull.json ${D}/usr/share/myir/board_cfg.json
      fi

      install -m 0755 ${S}/mxde.xml ${D}/usr/share/myir/
      install -m 0755 ${S}/settings.ini ${D}/usr/share/myir/
      install -m 0755 ${S}/psplash ${D}/usr/bin/
      install -m 755 ${S}/init_boardcfg.py ${D}/usr/share/myir/
}

FILES_${PN} = "/home/myir/ \
	       /usr/share/myir/ \
	       /usr/share/myir/www/ \
	       /usr/share/myir/www/* \
	       /usr/share/myir/*/* \
	       /lib/ \
	       /usr/bin/ \
             "

TARGET_CC_ARCH += "${LDFLAGS}"
INSANE_SKIP_${PN}-dev = "ldflags"
INSANE_SKIP_${PN} = "${ERROR_QA} ${WARN_QA}"
```

&emsp;&emsp;下面介绍在系统中加入qt-demo,在目录fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir下建立如下目录结构：
```
├── qt-demo
   └── qt-demo.bb

```
qt-demo.bb的内容如下： 
```
DESCRIPTION = "qt app"
DEPENDS = "zlib glibc ncurses "
SECTION = "libs"
LICENSE = "MIT"
PV = "3"
PR = "r0"

LIC_FILES_CHKSUM = "file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SRCREV = "ba71eadf84c2b57a2a751aae89ac453c7d05bef2"
SRC_URI = " \ 
	    git://github.com/hufan/web-demo-bb;protocol=https;branch=qt-app \
          "
S_G = "${WORKDIR}/git"

do_install () {
      install -d ${D}/usr/share/myir/
      install -d ${D}/usr/share/applications/
      install -d ${D}/usr/share/pixmaps/
      install -d ${D}/usr/lib/fonts/
      install -d ${D}/lib/
      install -d ${D}/home/myir/

      cp -r ${S_G}/applications/* ${D}/usr/share/applications/
      cp -r ${S_G}/pixmaps/* ${D}/usr/share/pixmaps/
      cp -r ${S_G}/msyh.ttc ${D}/usr/lib/fonts/
      cp  -rfav ${S_G}/so/*.so*  ${D}/lib/
      cp   ${S_G}/qt-app/*  ${D}/home/myir/

}

FILES_${PN} = "/home/myir/ \
	     /usr/share/myir/ \
	     /usr/lib/fonts/ \
	     /lib/ \
	     /usr/share/applications/ \
	     /usr/share/pixmaps/ \
             "

#For dev packages only
INSANE_SKIP_${PN}-dev = "ldflags"
INSANE_SKIP_${PN} = "${ERROR_QA} ${WARN_QA}"
```

- SRC_URI : 指定源文件
- LIC_FILES_CHKSUM : 文件和对应的md5值
- do_compile、do_install : 执行bitbake的方法，编译源码和安装程序到文件系统
- FILES_${PN} : 添加支持的目录
- SRCREV : 指定使用软件的版本，可以根据实际情况修改

&emsp;&emsp;然后还需在构建文件系统前加入web-demo.bb任务，参考 表5-1-2 修改对应文件系统的bbappend文件，添加如下内容：  

```
	...
	web-demo \
	qt-demo \
	...
```

&emsp;&emsp;最后开始构建系统，如构建带qt的文件系统，则执行命令: `bitbake fsl-image-qt5`。

&emsp;&emsp;关于文件系统的构建，可以参考MYD-Y6ULX发布的文档MYD-Y6ULX-LinuxDevelopmentGuide_zh.pdf的3.3章节。



### 6.2 AM437X,AM335X系列开发板上集成MEasy HMI应用 

&emsp;&emsp;MEasy HMI包含本地QT应用和Web端应用，开发编译完成之后，最终都是在buildroot中打包生成的文件系统。各个平台通用的部分,包括本地HMI应用和Web HMI应用都于位于`myir-buildroot/board/myir/common/HMI`目录下面。板级配置相关的文件分别位于各自的`myir-buildroot/board/myir/myd_xxx/rootfs-overlay/usr/share/myir/board_cfg.json`文件中。
```
#!/bin/sh -e
# File: board/myir/myd_xxx/post-build.sh

	cp -a board/myir/common/HMI/*  output/target
	
	...

```
&emsp;&emsp;在buildroot执行make的时候上述目录的文件都会通过执行上述`myir-buildroot/board/myir/myd_xxx/post-build.sh`脚本拷贝至文件系统对应的目录，例如`myir-buildroot/board/myir/common/HMI/home/myir`目录下的文件会拷贝至文件系统`/home/myir`目录下面。最终生成的目标文件系统位于`myir-buildroot/output/target`目录，在buildroot编译的最后阶段会根据这个目标文件系统生成各种格式的文件系统。  
