### 3.4 添加应用到本地HMI

&emsp;&emsp;本章节主要讲述向MEasy本地HMI中添加的用户的应用。用户如果需要在MEasy本地HMI中显示用户的应用，只需要一下几步就可以完成操作。

* 创建用户的Qt Widgets Application类型的应用命名为user\_app，使用上述编译环境编译完成后拷贝至开发板_/home/myir_目录下面
* 为这个应用创建一个192\*192分辨率的图标user\_app.png，拷贝至开发板_/usr/share/pixmaps_目录下面
* 在开发板_/usr/share/applications_目录下创建一个属于用户的桌面配置文件，命名以数字开头例如09\__user_\_app.desktop，配置文件里面内容如下：

```
[Desktop Entry]
Name=user_app
Name[zh_TW]=用户应用
Name[zh_CN]=用户应用

Type=Application
Icon=/usr/share/pixmaps/user_app.png
Exec=/home/myir/user_app --platform linuxfb
Terminal=false
MimeType=application/x-directory;inode/directory;
Categories=System;FileTools;Utility;Qt;FileManager;
```

* 完成上述步骤以后，重新启动开发板，就可以看到用户的应用出现在MEasy本地HMI的界面中。



