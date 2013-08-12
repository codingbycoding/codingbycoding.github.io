#!/bin/python
##python in linux hash bang

###!/usr/local/bin/python #python in linux hash bang

"this is pytest"

def FuncTest(x):
    print("Yes" + x)


class ClassTest(object):
    """   """
    def __init__(self):
        print("class ClassTest: " + "__init__")
        self.str1 = 'abc'
        self.ClassName = 'ClassTest'
        self.ClassVersion = '0.1'

    def toString(self):
        print 'ClassName:%s ClassVersion:%s' % (self.ClassName, self.ClassVersion)

    @staticmethod    
    def staticMethodTestOne():
        print 'staticMethodTestOne called'
        
    def staticMethodTest():
        print 'staticMethodTest called'
    staticMethodTest = staticmethod(staticMethodTest)
        
        
    def classMethodTest():
        print 'classMethodTest called'

    classMethodTest = classmethod(classMethodTest)

    @classmethod
    def classMethodTestOne():
        print 'classMethodTestOne called'
         

    def showName(self):
        print "ClassTest"

        
def testMain():
    """ """
    print "HelloWorld"        
    FuncTest("No")    
    c1 = ClassTest()    

    a1=1
    a1_1=1

    
    a200000_1=200000
    a200000_2=200000
    stra_1="abcd"
    stra_2="abcd"
    print id(a1)
    print id(a1_1)
    print id(a200000_1)
    print id(a200000_2)
    print id(stra_1)
    print id(stra_2)



    for i in range(1,10):
        print '*',


        
    import sys
    print len(sys.argv)
    print str(sys.argv)

# for key in sys.argv:
#     print sys.argv[key]

    import os
    cwd = os.getcwd()
    print 'current directory:', cwd
    print os.listdir(cwd)





testMain()


assert 1==1

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
ClassTest.staticMethodTest()
# ClassTest.classMethodTestOne()
ClassTest.staticMethodTestOne()

if __name__ == '__main__':
    print 'in __main__ in pytest.py'
    filename = 'filename.py'
    f = open(filename, 'r')
    exec f
# or execfile(filename, globals=globals(), locals=locals())



# import
print '*************************'
import filename   



import os
result = -1
# result = os.system("start cmd")
print 'result: %d' % result

print 'The End.'


if sys.platform != 'win32':
    ret = os.fork()
    if ret == 0:
        print 'child process'

    elif ret > 0:
        print 'parent process'

    else:
        print 'error happened.'




import re
m = re.match('f[12]oo', 'testf1oojackf2oo;')
if m is not None:
    print m.group()
else:
    print 'match failed.'


s = re.search('f[12]oo', 'testf1oojackf2oo;')
if s is not None:
    print s.group()
else:
    print 'search failed'

    
    
