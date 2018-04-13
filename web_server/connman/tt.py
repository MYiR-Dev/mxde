
import pyconnman
manager = pyconnman.ConnManager()
technologies = manager.get_technologies()
print '========================================================='
for i in technologies:
    (path, params) = i
    print path, '['+params['Name']+']'

print '1========================================================='
print '2========================================================='
print '3========================================================='
print '4========================================================='

services = manager.get_services()
print '========================================================='
for i in services:
    (path, params) = i
    print path, '['+params['Name']+']'

