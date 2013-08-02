#!/usr/bin/python
"""
this is to modify services.xml TmServices-0.1.0.jar/proxool.xml
and launch Gate Grid Node
"""

VersionBase = '20130722R1'
PathBase = '/home/ztgame/plaonline/'

#DSVersion = 'S' + VersionBase
# configFile = PathBase + 'config.xml'
# servicesxmlFile = PathBase + DSVersion + '/' + 'DC/' + 'config/' + 'services.xml'
configFile = 'config.xml'
servicesxmlFile = 'services.xml' 

cpLibs = ''
cpoptionPattern =

JedisNameContent= 'TmOnline.Jedis.Address'
JedisAddressInXML =


def ProcessServices_xml():
    try:
        f = open(servicesxmlFile, 'r')    
        tree = ElementTree.parse(f)
    except IOError, e:
        print 'open file' + configFile + 'error: ', e
        f.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        f.close()
        exit(1)
        
    for tag in tree.getiterator('property'):        
        nameContent = tag.attrib.get('name')
        if nameContent == JedisNameContent:
            argDcAddress += inip
            DcAddressInDSACfg += inip + '\n'
            print 'inip: ' + inip        


from xml.etree import ElementTree
import sys
import os

for arg in sys.argv:
    print arg

#os.system('start cmd')

# import subprocess
# subprocess.call(['notepad'])
def Processservicesxml():
    
    

def ProcessJar():
    os.system('jar xvf TmServices-0.0.0.jar proxool.xml')

    
    os.system('jar uvf TmServices-0.1.0.jar proxool.xml')
    os.system('rm -f proxool.xml')
    
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
