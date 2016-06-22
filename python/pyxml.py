#!/usr/bin/python
from xml.etree import ElementTree
import sys
import os

for arg in sys.argv:
    print arg

#os.system('start cmd')

# import subprocess
# subprocess.call(['notepad'])
def ParseArgs(ID=1):
    with open('config.xml', 'rt') as f:
        tree = ElementTree.parse(f)


    strID = str(ID)     
    argDcAddress = '--DcAddress='
    argDcPort = '--DcPort=6020'
    argDsaType = '--DsaType='
    argMaxLoad = '--MaxLoad='          
    # for node in tree.iter():
    for node in tree.getiterator('GATE'):        
        #print node.tag
        inip = node.attrib.get('INIP')
        if inip:
            argDcAddress += inip
            print inip
            
    for node in tree.getiterator('GAME'):        
        #print node.tag
        if node.attrib.get('ID') == strID:
            print node.attrib.get('ID')
            DsaType = node.attrib.get('DsaType')
            if DsaType:
                print 'DsaType: %s' % DsaType
                argDsaType += DsaType
            MaxLoad = node.attrib.get('MaxLoad')
            if MaxLoad:
                print 'MaxLoad %s' % MaxLoad
                argMaxLoad += MaxLoad    
            
    return argDcAddress, argDcPort, argDsaType, argMaxLoad          

            
def TestThreading():        
    import threading
    t = threading.Thread(target='', args=())
    t.start()
    t.join()            

    
if __name__ == '__main__':
    print '__main__'
    # with open('config.xml', 'rt') as f:
    #     tree = ElementTree.parse(f)

    # # for node in tree.iter():
    # for node in tree.getiterator('GAME'):        
    #     #print node.tag
    #     inip = node.attrib.get('INIP')
    #     if inip:
    #         print inip
            
    ret1 = os.fork()
    if ret1 == 0:
        ret2 = os.fork()
        if ret2 == 0:
            argDcAddress, argDcPort, argMaxLoad, argDsaType = ParseArgs()
            print 'argDcAddress: %s, argDcPort: %s, argMaxLoad: %s, argDsaType: %s' \
            % \
            (argDcAddress, argDcPort, argMaxLoad, argDsaType)
            TestExe = '/cygdrive/c/Windows/notepad.exe'
            #os.execv(TestExe, [TestExe, '172.30.201.135'])
            # os.execv('/DsAgent', [argDcAddress, argDcPort, argDsaType, argMaxLoad])
            sys.exit()
        elif ret2 > 0:
            print 'this is second parent process'
            sys.exit()
        else:
            print 'fork error happened'
    
    
    elif ret1 > 0:
        print 'this is top parent process'
    else:
        print 'fork error happened'        
