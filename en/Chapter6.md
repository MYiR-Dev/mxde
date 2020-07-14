## 6  MEasy HMI Applications Integration 

---

In the previous chapter we introduced the directory structure of the MEasy HMI on the target board, as well as the runtime environment and development process of the local HMI and Web HMI. This chapter will focus on how to integrate the MEasy HMI application into the target board system. Then the MEasy HMI starts up on the development board.


### 6.1 Integrate MEasy HMI Application on i.MX6UL Series Development Boards 
 
A package in Yocto is placed in a bb file, then a very large number of bb files integrate a recipe, and then many recipes form a meta layer. Users can add a soft Package by adding a bb (bitbake configuration file) file to the recipe.
So, we can add web HMI to our system by adding the following web-demo.bb to fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir:
```
└── web-demo
    └── web-demo.bb
```

The source code of web-demo.bb is shown as below:
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
The following describes how to integrate the local HMI into our system by adding the qt-demo.bb file to fsl-release-yocto/sources/meta-myir-imx6ulx/recipes-myir:
```
├── qt-demo
   └── qt-demo.bb

```

The source code of qt-demo.bb is shown as below: 
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


- SRC_URI : Specify the source file 
- LIC_FILES_CHKSUM : File and corresponding md5 values 
- do_compile、do_install : Perform bitbake method, compile source code and install program to file system 
- FILES_${PN} : Add a supported directory
- SRCREV : Specifies the version of the software to use. It can be modified according to the actual situation

Then you need to add the web-demo.bb task before building the file system. Refer to Table 5-1-2 to modify the bbappend file of the corresponding file system and add the following content:
```
	...
	web-demo \
	qt-demo \
	...
```

Finally start building the system, such as building a file system with qt, then execute the command: `bitbake fsl-image-qt5`

For the construction of the file system, refer to the Chapter3.3  of the document MYD-Y6ULX-LinuxDevelopmentGuide_en.pdf published by MYD-Y6ULX.



### 6.2 Integrate MEasy HMI Application on AM335X,AM437X Series Development Boards

MEasy HMI contains local QT5 applications, Web back-end and Web front-end. After we have finished developing the applications seperately, we should integrate them into the rootfs system. For buildroot, we put the common files of local HMI applications and Web HMI applications into `myir-buildroot/board/myir/common/HMI`, and put the different board configuration file into `myir-buildroot/board/myir/myd_xxx/rootfs-overlay/usr/share/myir/board_cfg.json`.
```
#!/bin/sh -e
# File: board/myir/myd_xxx/post-build.sh

	cp -a board/myir/common/HMI/*  output/target
	
	...

```
When builing the rootfs system in `Buildroot`, all the file will be copied to `myir-buildroot/output/target` by a shell scripts `myir-buildroot/board/myir/myd_xxx/post-build.sh`. 
