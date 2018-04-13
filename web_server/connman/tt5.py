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

technology = manager.GetTechnologies()

for entry in technology:
	path = entry[0]
	properties = entry[1]

	print "[ %s ]" % (path)

	for key in properties.keys():
		val = str(properties[key])
		print "    %s = %s" % (key, val)
	print
