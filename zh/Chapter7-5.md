### 7.5 Connman

Connman这个网络管理的服务提供的dbus方法和信号比较多，我们这里只讲述我们MEasy HMI用使用到的方法和信号。

```
                        <method name="GetServices">
                            <arg name="services" type="a(oa{sv})" direction="out"/>
                        </method>
                        <method name="SetProperty">
                            <arg name="name" type="s" direction="in"/>
                        </method>
                        <signal name="PropertyChanged">
                            <arg name="name" type="s"/>
                            <arg name="value" type="v"/>
                        </signal>
                        <signal name="ServicesChanged">
                            <arg name="changed" type="a(oa{sv})"/>
                            <arg name="removed" type="ao"/>
                        </signal>
```

方法：

GetServices 获取当前开发板可用的网口服务的方法

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| services | a(oa{sv}) | QDBusArgument类 | 示例如下 |

```
array [
      struct {
         object path "/net/connman/service/ethernet_689e19bc1c84_cable"
         array [
            dict entry(
               string "Type"
               variant                   string "ethernet"
            )
            dict entry(
               string "IPv4"
               variant                   array [
                     dict entry(
                        string "Method"
                        variant                            string "dhcp"
                     )
                     dict entry(
                        string "Address"
                        variant                            string "192.168.30.120"
                     )
                     dict entry(
                        string "Netmask"
                        variant                            string "255.255.255.0"
                     )
                     dict entry(
                        string "Gateway"
                        variant                            string "192.168.30.1"
                     )
                  ]
            )
      }
   ]
```

方法：

SetProperty 设置网口信息

输入：

| 参数 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| name | s | 网口设置项名称 | 示例如下 |

```
   string "IPv4.Configuration"
   variant       array [
         dict entry(
            string "Method"
            variant                string "dhcp"
         )
      ]
```

信号：

PropertyChanged 网口信息改变的信号

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| name | s | 网口设置项名称 | "IPv4" |
| value | v | 设置项的值 | 示例如下 |

```
   variant       array [
         dict entry(
            string "Method"
            variant                string "dhcp"
         )
         dict entry(
            string "Address"
            variant                string "192.168.30.149"
         )
         dict entry(
            string "Netmask"
            variant                string "255.255.255.0"
         )
      ]
```

信号：

ServicesChanged 网口变动的信号

返回值：

| 名称 | 类型 | 说明 | 示例 |
| :--- | :--- | :--- | :--- |
| remove | ao | QDBusArgument类 | 示例如下 |
| changed | a(oa{sv}) | QDBusArgument类 | 示例如下 |

```
   array [
      struct {
         object path "/net/connman/service/ethernet_689e19bc1c84_cable"
         array [
         ]
      }
   ]
   array [
      object path "/net/connman/service/ethernet_689e19bc1c86_cable"    //remove
   ]
```



