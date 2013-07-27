#!/usr/local/bin/python #python in linux hash bang

def FuncTest(x):
    print("Yes" + x)


class ClassTest(object):
    """   """
    def __init__(self):
        print("class ClassTest: " + "__init__")

    def showName(self):
        print "ClassTest"

        


print "HelloWorld"        
FuncTest("No")    
c1 = ClassTest()    
c1.showName()

import sys
print sys.platform


tuple1 = ('jack', 200, 'yes', 300)
list1 = ['listnumber', 300, 200, 'ok']
print tuple1
print list1

# if true :
#     print jack
print dir(list)


i=0
while (i < 30):
    i+=1
    print '*',
    # print '*'
print dir(tuple)


print type(('abc'))
print type(('abc', ))

dict1={'IP':'127.0.0.1', 'Port':'6020'}
print dict1

for key in dict1:
    print 'key=%s value=%s' % (key, dict1[key])




ax = lambda x1, x2=10 : x1 + x2
print ax(20)
