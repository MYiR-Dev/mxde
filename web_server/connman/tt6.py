#!/usr/bin/python

import dbus

def extract_values(values):
	val = "{"
	for key in values.keys():
		val += " " + key + "="
		if key in ["Servers", "Excludes"]:
			val += extract_list(values[key])
		else:
			val += str(values[key])
	val += " }"
	return val

def extract_list(list):
	val = "["
	for i in list:
		val += " " + str(i)
	val += " ]"
	return val

bus = dbus.SystemBus()

manager = dbus.Interface(bus.get_object('net.connman', '/'),
					'net.connman.Manager')

services = manager.GetServices()

for entry in services:
	path = entry[0]
	properties = entry[1]

	print "[ %s ]" % (path)

	for key in properties.keys():
		if key in ["Strength"]:
			val = int(properties[key])
			print " Wifi AP Signal Strength or P2P device signal strength  %s = %s" % (key, val)
		elif key in ["Name"]:
			val = str(properties[key])
			print " Name of the AP/P2P device is %s = %s" % (key, val)
		else:
				val = str(properties[key])
	print
