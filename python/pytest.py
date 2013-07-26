#!/usr/local/bin/python #python in linux hash bang
"this is pytest"

def FuncTest(x):
    print("Yes" + x)


class ClassTest(object):

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

ClassTest.staticMethodTest()
# ClassTest.classMethodTestOne()
ClassTest.staticMethodTestOne()

if __name__ == '__main__':
    print 'in __main__'
    filename = 'filename.py'
    f = open(filename, 'r')
    exec f
    
