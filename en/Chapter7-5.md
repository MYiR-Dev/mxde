### 7.5 Connman

Connman's network management service provides more dbus methods and signals. Here we only describe the methods and signals used by our MEasy HMI.

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

Method：

GetServices Method for obtaining network port service available in current development board

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| services | a(oa{sv}) | QDBusArgument class | Examples are as follows |

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

Method:

SetProperty Method of set network port information

Input：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| name | s | Network port setting item name | Examples are as follows |

```
   string "IPv4.Configuration"
   variant       array [
         dict entry(
            string "Method"
            variant                string "dhcp"
         )
      ]
```

Method：

PropertyChanged  Network port change signal

Return：

| Name | Type | Description | Example |
| :--- | :--- | :--- | :--- |
| name | s | Network port setting item name | "IPv4" |
| value | v | Set the value of the item | Examples are as follows |

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

Signal：

ServicesChanged Network port signal

Return：

| Name | ASCII type-code | Description | Example |
| :--- | :--- | :--- | :--- |
| remove | ao | QDBusArgument class | Examples are as follows |
| changed | a(oa{sv}) | QDBusArgument class | Examples are as follows |

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



