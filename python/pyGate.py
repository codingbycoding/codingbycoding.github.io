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


cpoptionPattern = 'E:\\PLAOnline\\Server\\lib\\'
#cpoptionPatternSub = '/home/ztgame/plaonline/' + 'S' + VersionBase + '/DC/Node/'
#cpContent = '/home/ztgame/plaonline/' + 'S' + VersionBase + '/DC/Node/TmServices-0.1.0.jar' + ':/home/ztgame/plaonline/' + 'S' + VersionBase

PlatformUrlNameAttribLabel = 'TmOnline.PlatformUrl'
PlatformUrlValueContent = 'http://180.201.20.11:8080/plagame/plaservice'


JedisNameContent = 'TmOnline.Jedis.Address'
JedisValueContent = ''

ServerZoneNameLabel = 'TmOnline.ServerZone'
ServerZoneValueContent = ''
ServerZoneIdNameLabel = 'TmOnline.ServerZoneId'
ServerZoneIdValue = ''
ServerGameIdName = 'TmOnline.ServerGameId'
ServerGameIdValue = ''
duduaddrName = 'dudu.addr'
duduaddrValue = ''



LogActionFileName = 'log4j.appender.ActionFile.file'
LogOrderObjFileName = 'log4j.appender.OrderObjFile.file'
LogOrderListFileName = 'log4j.appender.OrderListFile.file'
LogKeepFileName = 'log4j.appender.KeepFile.file'


JarFileName = 'TmServices-0.1.0.jar'


from xml.etree import ElementTree
import sys
import os

def paramInit(filename = configFile):
    global JedisValueContent
    global PlatformUrlValueContent
    global ServerZoneValueContent
    global ServerZoneIdValue
    global ServerGameIdValue


    try:
        f = open(filename, 'r')
        tree = ElementTree.parse(f)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        f.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        f.close()
        exit(1)

    tag = tree.getiterator('GATE')
    if tag:
        PlatformUrlValueContent = tag[0].get('PlatformUrl')
        ServerZoneValueContent = tag[0].get('ServerZone')
        ServerZoneIdValue = tag[0].get('ServerZoneId')
        ServerGameIdValue = tag[0].get('ServerGameId')

    redisTag = tree.getiterator('REDIS')
    if redisTag:
        JedisValueContent = redisTag[0].get('IP')
        print 'JedisValueContent:', JedisValueContent
        
    f.close()
    
    
# def ProcessServices_xml():
def PSX(filename = servicesxmlFile):
    paramInit()
    filenameTmp = filename + '.tmp.xml'
    
    try:
        f = open(filename, 'r')
        tree = ElementTree.parse(f)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        f.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        f.close()
        exit(1)

    #option tag -cp
    NextIsCPFlag = False    
    for tag in tree.getiterator('option'):
        if NextIsCPFlag:
            print '-cp real content: ' + tag.text
            tag.text = 'test to write'
            NextIsCPFlag = False
            
        if tag.text and tag.text == '-cp' :
            NextIsCPFlag = True

    #property tag
    for tag in tree.getiterator('property'):
        if tag.get('name') == JedisNameContent:
            tag.set('value', JedisValueContent)
            # print tag.get('name')
            # print tag.get('value')
        elif tag.attrib.get('name') == PlatformUrlNameAttribLabel:
            tag.set('value', PlatformUrlValueContent)
        elif tag.attrib.get('name') == ServerZoneNameLabel:
            tag.set('value', ServerZoneValueContent)
        elif tag.attrib.get('name') == ServerZoneIdNameLabel:
            tag.set('value', ServerZoneIdValue)
        elif tag.attrib.get('name') == ServerGameIdName:
            tag.set('value', ServerGameIdValue)

        elif tag.attrib.get('name') == LogActionFileName:
            tmpStr = tag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:
                tag.attrib.set('value', tmpStrSub)
        elif tag.attrib.get('name') == LogOrderObjFileName:
            tmpStr = tag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                tag.attrib.set('value', tmpStrSub)
        elif tag.attrib.get('name') == LogOrderListFileName:
            tmpStr = tag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                tag.attrib.set('value', tmpStrSub)
        elif tag.attrib.get('name') == LogKeepFileName:
            tmpStr = tag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                # tag.attrib.set('value', tmpStrSub)
                tag.attrib.set('value', tmpStrSub)            

    tree.write(filenameTmp)
    f.close()
    
    # os.system('mv -f ' + filenameTmp + ' ' + filename)             
    # os.system('rm -f ' + filenameTmp)
    
#     for tag in tree.getiterator('server-template'):    
#     # for tag in tree.getiterator('icegrid.application.server-template.icebox.property'):
# #       print tag.get()
#         print tag.keys()
#         print tag.items()
# #        print 'tag: ' + tag
#         value = tag.attrib.get('option')
#         if value:
#             print 'value: ' + value
#         # if nameContent == JedisNameContent:
#         #     argDcAddress += inip
#         #     DcAddressInDSACfg += inip + '\n'
#         #     print 'inip: ' + inip        




def ProcessArg():
    for arg in sys.argv:
        print arg

#os.system('start cmd')

# import subprocess
# subprocess.call(['notepad'])
    

def ProcessJar(filename = configFile):
    os.system('jar xvf ' + JarFileName + ' proxool.xml')

    try:
        f = open(filename, 'r')
        tree = ElementTree.parse(f)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        f.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        f.close()
        exit(1)

    tag = tree.getiterator('DB')
    if tag:
        print tag
        db_ip = tag[0].get('IP')
        db_name = tag[0].get('DATABASE')
        db_user = tag[0].get('USERNAME')
        db_passwd = tag[0].get('PASSWD')

        print db_ip, db_name, db_user, db_passwd

        # db_ip = tag[0]
        # db_name = tag[1]
        # db_user = tag[2]
        # db_passwd = tag[3]
    f.close()

    filenameproxool = "proxool.xml"
    try:
        fproxool = open(filenameproxool, 'r')
        treeproxool = ElementTree.parse(fproxool)
    except IOError, e:
        print 'open file' + filenameproxool + 'error: ', e
        fproxool.close()
        exit(1)
    except Exception, e:
        print 'Exception: ', e
        fproxool.close()
        exit(1)

    # tag = tree.getiterator('driver-url')
    urlelem = treeproxool.find('driver-url')
    urlcontent = treeproxool.findtext('driver-url')
    if urlcontent:
        print urlcontent
        urlcontentrep1 = urlcontent.replace("localhost", db_ip)
        urlcontentrep2 = urlcontentrep1.replace("tmdatacenter", db_name)
        urlelem.text = urlcontentrep2

        print urlcontentrep1, urlcontentrep2, urlelem.text
        
    for tag in treeproxool.getiterator('property'):
        if tag.attrib.get('name') == "user":
            tag.set('value', db_user)
            
        elif tag.attrib.get('name') == "password":
            tag.set('value', db_passwd)

    filenameTmp = "proxool.xml.tmp"
    treeproxool.write(filenameTmp)

    fproxool.close()
    os.system('mv ' + filenameTmp + ' proxool.xml')
    os.system('jar uvf ' + JarFileName + ' proxool.xml')
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
            
    # ret1 = os.fork()
    # if ret1 == 0:
    #     ret2 = os.fork()
    #     if ret2 == 0:
    #         argDcAddress, argDcPort, argMaxLoad, argDsaType = ParseArgs()
    #         print 'argDcAddress: %s, argDcPort: %s, argMaxLoad: %s, argDsaType: %s' \
    #         % \
    #         (argDcAddress, argDcPort, argMaxLoad, argDsaType)
    #         TestExe = '/cygdrive/c/Windows/notepad.exe'
    #         #os.execv(TestExe, [TestExe, '172.30.201.135'])
    #         # os.execv('/DsAgent', [argDcAddress, argDcPort, argDsaType, argMaxLoad])
    #         sys.exit()
    #     elif ret2 > 0:
    #         print 'this is second parent process'
    #         sys.exit()
    #     else:
    #         print 'fork error happened'
    
    
    # elif ret1 > 0:
    #     print 'this is top parent process'
    # else:
    #     print 'fork error happened'        


    
    # ProcessJar()
    PSX()
    # exit with return value: 0 is success other is failed
    exit(0)     
