### 3.4 Add an Application to HMI

This chapter focuses on the application of the user added to the MEasy HMI.

If users want to display the user's application in the MEasy HMI, it only takes a few steps to complete the operation.

* Create a user's Qt Widgets Application type application named user\_app, use the above compiler environment compiled and copied to the development board _/home/myir_ directory below
* Create a 192\*192 resolution icon user\_app.png for this application, copy it to the development board_ /usr/share/pixmaps _directory
* Create a desktop configuration file belonging to the user in the development board _/usr/share/applications_ directory. Start with a number such as 09\_user\_app.desktop. The contents of the configuration file are as follows:

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

* After completing the above steps, restart the development board and you will see that the user's application appears on the MEasy HMI interface.



