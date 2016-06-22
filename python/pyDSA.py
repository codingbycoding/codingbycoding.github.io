#!/usr/bin/python
"""
this is to modify DSA.cfg base ID passed from up order
and pass arguments base on config.xml to launch DsAgent.
"""

from xml.etree import ElementTree
import sys
import os
import re



#os.system('start cmd')

# import subprocess
# subprocess.call(['notepad'])
VersionBase = '20130722R1'
PathBase = '/home/ztgame/plaonline/'

DSVersion = 'S' + VersionBase
# configFile = PathBase + 'config.xml'
# DSAConfigFile = PathBase + DSVersion + '/' + 'DSA/' + 'config/' + 'DSA.cfg'
configFile = 'config.xml'
DSAConfigFile = 'DSA.cfg' 
    

DcAddressSearchPattern = 'DcAddress[ ]*=[ ]*[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}[ ]*'
DcPortSearchPattern = 'DcPort[ ]*=[ ]*\d{4,5}'
MaxLoadSearchPattern = 'MaxLoad[ ]*=[ ]*\d+'
DsaTypeSearchPattern = 'DsaType[ ]*=[ ]*\d+'
DS_IPSearchPattern = 'DS_IP[ ]*=[ ]*[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}[ ]*'


DcAddressInDSACfg = 'DcAddress='
DcPortInDSACfg = 'DcPort=6020'
MaxLoadInDSACfg = 'MaxLoad='
DsaTypeInDSACfg = 'DsaType='
DS_IPInDSACfg = 'DS_IP='



def ParseArgs(ID = 1):

    try:
        #with open(configFile, 'rt') as f:
        f = open(configFile, 'rt')    
        tree = ElementTree.parse(f)
    except IOError, e:
        print 'open file' + configFile + 'error: ', e
        f.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        f.close()
        exit(1)
            
        
    global DcAddressInDSACfg
    global DcPortInDSACfg
    global MaxLoadInDSACfg
    global DsaTypeInDSACfg
    global DS_IPInDSACfg

    strID = str(ID)     
    argDcAddress = '--DcAddress='
    argDcPort = '--DcPort=6020'
    argDsaType = '--DsaType='
    argMaxLoad = '--MaxLoad='
    argDS_IP = '--DS_IP='
    # for tag in tree.iter():
    for tag in tree.getiterator('GATE'):        
        #print tag.tag
        inip = tag.attrib.get('INIP')
        if inip:
            argDcAddress += inip
            DcAddressInDSACfg += inip + '\n'
            print 'inip: ' + inip
            
    for tag in tree.getiterator('GAME'):        
        #print tag.tag
        if tag.attrib.get('ID') == strID:
            print 'tag.attrib.get(\'ID\'): ' +  tag.attrib.get('ID')
            DsaType = tag.attrib.get('DsaType')
            if DsaType:
                print 'DsaType: %s' % DsaType
                argDsaType += DsaType
                DsaTypeInDSACfg += DsaType + '\n'
            MaxLoad = tag.attrib.get('MaxLoad')
            if MaxLoad:
                print 'MaxLoad %s' % MaxLoad
                argMaxLoad += MaxLoad
                MaxLoadInDSACfg += MaxLoad + '\n'
            DS_IP = tag.attrib.get('EXIP')
            if DS_IP:
                print 'EXIP %s' % DS_IP
                argDS_IP += DS_IP
                DS_IPInDSACfg += DS_IP + '\n'

    f.close()            
    return argDcAddress, argDcPort, argDsaType, argMaxLoad, argDS_IP



def ProcessDSACfg(filename = DSAConfigFile):

    ParseArgs()
    
    global DcAddressInDSACfg
    global DcPortInDSACfg
    global MaxLoadInDSACfg
    global DsaTypeInDSACfg
    global DS_IPInDSACfg
    
    filenameTmp = filename + '.tmp'

    try:
        fileDSACfg = open(filename, 'r')
        fileDSACfgTmp = open(filenameTmp, 'w')
    except IOError, e:
        print 'open file ' + filename + 'error: ' , e
        fileDSACfg.close()
        fileDSACfgTmp.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        fileDSACfg.close()
        fileDSACfgTmp.close()
        exit(1)
        
    
    newDSACfg = '# new config file from DSA.cfg \n'
    newDSACfgLines = []
    newDSACfgLines.append(newDSACfg)
    
    for eachLine in fileDSACfg:
        #
        subDcAddress = re.sub(DcAddressSearchPattern, DcAddressInDSACfg, eachLine)
        subDcPort = re.sub(DcPortSearchPattern, DcPortInDSACfg, eachLine)
        subDsaType = re.sub(DsaTypeSearchPattern, DsaTypeInDSACfg, eachLine)
        subMaxLoad = re.sub(MaxLoadSearchPattern, MaxLoadInDSACfg, eachLine)
        subDS_IP = re.sub(DS_IPSearchPattern, DS_IPInDSACfg, eachLine)

        print 'eachLine: ' +  eachLine

        searchFoundDcAddress = re.search(DcAddressSearchPattern, eachLine)
        searchFoundDcPort = re.search(DcPortSearchPattern, eachLine)
        searchFoundDsaType = re.search(DsaTypeSearchPattern, eachLine)
        searchFoundMaxLoad = re.search(MaxLoadSearchPattern, eachLine)
        searchFoundDS_IP = re.search(DS_IPSearchPattern, eachLine)
        
        if searchFoundDcAddress is not None:
            print 'subDcAddress: ' + subDcAddress
            newDSACfg += subDcAddress
            newDSACfgLines.append(subDcAddress)
        elif searchFoundDcPort is not None:
            print 'subDcPort: ' +  subDcPort
            newDSACfg += subDcPort
            newDSACfgLines.append(subDcPort)
        elif searchFoundDsaType is not None:
            print 'subDsaType: ' +  subDsaType
            newDSACfg += subDsaType
            newDSACfgLines.append(subDsaType)
        elif searchFoundMaxLoad is not None:
            print 'subMaxLoad: ' + subMaxLoad
            newDSACfg += subMaxLoad
            newDSACfgLines.append(subMaxLoad)
        elif searchFoundDS_IP is not None:
            print 'subDS_IP: ' + subDS_IP
            newDSACfg += subDS_IP
            newDSACfgLines.append(subDS_IP)
        #elif 
        else:
            newDSACfg += eachLine
            newDSACfgLines.append(eachLine)

    fileDSACfg.close()                
    fileDSACfgTmp.writelines(newDSACfgLines)        
    fileDSACfgTmp.close()
            
    os.system('mv -f ' + filenameTmp + ' ' + filename)             
    os.system('rm -f ' + filenameTmp)     
   
   
            
def TestThreading():        
    import threading
    t = threading.Thread(target='', args=())
    t.start()
    t.join()            

    
    
if __name__ == '__main__':
    print '__main__'

    for arg in sys.argv:
        print arg

    
    ret1 = os.fork()
    if ret1 == 0:
        ret2 = os.fork()
        if ret2 == 0:
            argDcAddress, argDcPort, argDsaType, argMaxLoad = ParseArgs()
            print 'argDcAddress: %s, argDcPort: %s, argMaxLoad: %s, argDsaType: %s' \
            % \
            (argDcAddress, argDcPort, argDsaType, argMaxLoad)
            TestExe = '/cygdrive/c/Windows/notepad.exe'
            os.execv(TestExe, [argDcAddress, argDcPort, argDsaType, argMaxLoad])
            # os.execve('/DsAgent', [argDcAddress, argDcPort, argDsaType, argMaxLoad], env)
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

    # exit with return value: 0 is success other is failed
    exit(0) 
