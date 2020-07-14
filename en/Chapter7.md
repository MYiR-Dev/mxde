## 7. Introduction of D-Bus API

---

This chapter focuses on the interface in the MYIR D-Bus library and the D-Bus interface provided by Connman, which is a network management service.

The interface of the MYIR D-Bus library is also created based on D-Bus. The D-Bus Methods and Signals are defined in the `mxde.xml` file in the `mxdbus` directory, it will be explained in detail in the following sections.

The QT applications with MYIR D-Bus library should add `Qt-Dbus` component and put the `mxde.xml' into the project. During the compiling, the corresponding QT signals and slots will be created.

