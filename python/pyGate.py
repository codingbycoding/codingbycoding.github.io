#!/usr/bin/python
"""
this is to modify services.xml TmServices-0.1.0.jar/proxool.xml DSA.cfg HPA.cfg 
"""
import time

VersionBase = '20130722R1'
PathBase = '/home/ztgame/plaonline/'

# these variables will be init by par
GServerType = ''
GServerID = '1'
# GVersion = ''


# error code define here

GERR_FILE = 2
GERR_PARAMETER = 3



GLogger = None

GDSAConfigFile = 'DSA.cfg'
#DSVersion = 'S' + VersionBase
# GConfigFile = PathBase + 'config.xml'
# servicesxmlFile = PathBase + DSVersion + '/' + 'DC/' + 'config/' + 'services.xml'
GConfigFile = 'config.xml'
servicesxmlFile = 'services.xml'


GcpoptionPattern = 'E:\\PLAOnline\\Server\\lib\\'
#GcpoptionPatternSub = '/home/ztgame/plaonline/' + 'S' + VersionBase + '/DC/Node/'
#cpContent = '/home/ztgame/plaonline/' + 'S' + VersionBase + '/DC/Node/TmServices-0.1.0.jar' + ':/home/ztgame/plaonline/' + 'S' + VersionBase

GPlatformUrlNameAttribLabel = 'TmOnline.PlatformUrl'
PlatformUrlValueContent = 'http://180.201.20.11:8080/plagame/plaservice'


JedisNameContent = 'TmOnline.Jedis.Address'
GJedisValueContent = ''

ServerZoneNameLabel = 'TmOnline.ServerZone'
ServerZoneValueContent = ''
ServerZoneIdNameLabel = 'TmOnline.ServerZoneId'
ServerZoneIdValue = ''
ServerGameIdName = 'TmOnline.ServerGameId'
ServerGameIdValue = ''
GduduaddrName = 'dudu.addr'
GduduaddrValue = ''

GGATEAttribNameList = []

LogActionFileName = 'log4j.appender.ActionFile.file'
LogOrderObjFileName = 'log4j.appender.OrderObjFile.file'
LogOrderListFileName = 'log4j.appender.OrderListFile.file'
LogKeepFileName = 'log4j.appender.KeepFile.file'


GJarFileName = 'TmServices-0.1.0.jar'


from xml.etree import ElementTree
import sys
import os


class Logger:
    ' '
    version = '0.1'
    logfile = None
    logfilehandle = None
    
    def __init__(self, logfile = 'pyLogger.log'):
        self.logfile = logfile
        
        try:
            self.logfilehandle = open(logfile, 'a')

            self.info('Another New Begin...')
        except IOError, e:
            print 'open file' + logfile + 'error: ', e
            self.logfilehandle.close()
            exit(GERR_FILE)
        except Exception, e:
            print 'Exception: ', e
            self.logfilehandle.close()
            exit(GERR_FILE)
            

    def currentTimestamp(self):
        curTS = time.strptime(time.ctime())
        retStr = "%4d%02d%02d %02d:%02d:%02d " % (curTS.tm_year, curTS.tm_mon, curTS.tm_mday, curTS.tm_hour,  curTS.tm_min, curTS.tm_sec)

        return retStr



    def __del__(self):
        self.info('This Is An End.')
        self.rawinfo('')
        self.rawinfo('')
        self.rawinfo('')
        self.logfilehandle.close()
        
    def rawinfo(self, msg):
        line2write = msg + '\n'
        self.logfilehandle.write(line2write)
        self.logfilehandle.flush()

        
    def info(self, msg):
        line2write = self.currentTimestamp() + ' INFO  *** ' + msg + '\n'
        self.logfilehandle.write(line2write)
        self.logfilehandle.flush()


    def warn(self, msg):
        line2write = self.currentTimestamp() + ' WARN  ### ' + msg + '\n'
        self.logfilehandle.write(line2write)
        self.logfilehandle.flush()

        
    def error(self, msg):
        line2write = self.currentTimestamp() + ' ERROR !!! ' + msg + '\n'
        self.logfilehandle.write(line2write)
        self.logfilehandle.flush()
        

        
def initialize():
    global GLogger
    GLogger = Logger()
    
    
        
    
    
def paramInit(filename = GConfigFile):
    ''' Init Some global variables '''
    global GJedisValueContent
    global PlatformUrlValueContent
    global ServerZoneValueContent
    global ServerZoneIdValue
    global ServerGameIdValue

    global GGATEAttribNameList

    try:
        configf = open(filename, 'r')
        tree = ElementTree.parse(configf)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        configf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        configf.close()
        exit(GERR_FILE)

    tag = tree.getiterator('GATE')
    if tag:
        print 'keys():'
        print tag[0].keys()
        print GGATEAttribNameList
        GGATEAttribNameList = tag[0].keys()
        print GGATEAttribNameList
        
        PlatformUrlValueContent = tag[0].get('PlatformUrl')
        ServerZoneValueContent = tag[0].get('ServerZone')
        ServerZoneIdValue = tag[0].get('ServerZoneId')
        ServerGameIdValue = tag[0].get('ServerGameId')

    redisTag = tree.getiterator('REDIS')
    if redisTag:
        GJedisValueContent = redisTag[0].get('IP')
        print 'GJedisValueContent:', GJedisValueContent
        
    configf.close()

    
def PDSA(configfile = GConfigFile, DSAConfigFile = GDSAConfigFile, IDNum = GServerID):
    ''' Process DSA.cfg '''
    
    try:
        configf = open(configfile, 'r')
        configtree = ElementTree.parse(configf)
    except IOError, e:
        print 'open file' + configfile + 'error: ', e
        configf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        # configf.close()
        exit(GERR_FILE)


    gametagfoundflag = False
    gametag = configtree.getiterator('GAME')
    for gametageach in gametag:
        # print gametageach.attrib.get('ID')
        # print 'IDNum:', IDNum
        if(gametageach.get('ID') == IDNum):
            gametagfound = gametageach
            gametagfoundflag = True
            # print 'gametagfound success'
            # print gametagfound.keys()
            
    if gametagfoundflag:
        print 'gametagfound.keys():'
        print gametagfound.keys()
        GGAMEAttribNameList = gametagfound.keys()
    else:
        print 'gametagfound failed'
        


    try:
        DSAConfigf = open(DSAConfigFile, 'r')
        lines = DSAConfigf.readlines()
        print 'lines:'
        print lines
    except IOError, e:
        print 'open file' + DSAConfigFile + 'error: ', e
        DSAConfigf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        # configf.close()
        exit(GERR_FILE)

        
    DSAConfigFileTmp = DSAConfigFile + '.tmp.cfg'
    try:
        DSAConfigTmpf = open(DSAConfigFileTmp, 'w')
        DSAConfigTmpf.writelines(lines)
        print 'lines to write:'
        print lines
    except IOError, e:
        print 'open file' + DSAConfigFileTmp + 'error: ', e
        DSAConfigTmpf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        # configf.close()
        exit(GERR_FILE)

        

        configf.close()
        DSAConfigf.close()
        DSAConfigTmpf.close()
        

def PHPA(configfile = GConfigFile):
    ''' Process HPA.cfg '''
    
    try:
        configf = open(configfile, 'r')
        configtree = ElementTree.parse(configf)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        configf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        # configf.close()
        exit(GERR_FILE)

    
    
    

# def ProcessServices_xml():
def PSX(filename = servicesxmlFile, configfile = GConfigFile):
# def PSX(filename = servicesxmlFile):
    '''Process services.xml file  '''
    
    paramInit()
    filenameTmp = filename + '.tmp.xml'

    try:
        configf = open(configfile, 'r')
        configtree = ElementTree.parse(configf)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        configf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        # configf.close()
        exit(GERR_FILE)

    gatetag = configtree.getiterator('GATE')
    if gatetag:
        print 'keys():'
        print gatetag[0].keys()
        GGATEAttribNameList = gatetag[0].keys()
        print GGATEAttribNameList

        
    try:
        servicesxmlf = open(filename, 'r')
        servicexmltree = ElementTree.parse(servicesxmlf)
    except IOError, e:
        print 'open file' + filename + 'error: ', e
        servicesxmlf.close()
        exit(GERR_FILE)
    except Exception, e:
        print 'Exception: ', e
        servicesxmlf.close()
        exit(GERR_FILE)

    #option tag -cp
    NextIsCPFlag = False    
    for optiontag in servicexmltree.getiterator('option'):
        if NextIsCPFlag:
            print '-cp real content: ' + optiontag.text
            optiontag.text = 'test to write'
            NextIsCPFlag = False
            
        if optiontag.text and optiontag.text == '-cp' :
            NextIsCPFlag = True

            
    #property tag
    for propertytag in servicexmltree.getiterator('property'):
        for gatetagattribeach in GGATEAttribNameList:
            if propertytag.get('name') == gatetagattribeach:
                propertytag.set('value', gatetag[0].get(gatetagattribeach))

    #here is Jedis
    for propertytag in servicexmltree.getiterator('property'):
        if propertytag.get('name') == JedisNameContent:
            propertytag.set('value', GJedisValueContent)
            
            # print tag.get('name')
            # print tag.get('value')
        # elif tag.attrib.get('name') == GPlatformUrlNameAttribLabel:
        #     tag.set('value', PlatformUrlValueContent)
        # elif tag.attrib.get('name') == ServerZoneNameLabel:
        #     tag.set('value', ServerZoneValueContent)
        # elif tag.attrib.get('name') == ServerZoneIdNameLabel:
        #     tag.set('value', ServerZoneIdValue)
        # elif tag.attrib.get('name') == ServerGameIdName:
        #     tag.set('value', ServerGameIdValue)
        #log path is process here
        elif propertytag.attrib.get('name') == LogActionFileName:
            tmpStr = propertytag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:
                propertytag.attrib.set('value', tmpStrSub)
        elif propertytag.attrib.get('name') == LogOrderObjFileName:
            tmpStr = propertytag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                propertytag.attrib.set('value', tmpStrSub)
        elif propertytag.attrib.get('name') == LogOrderListFileName:
            tmpStr = propertytag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                propertytag.attrib.set('value', tmpStrSub)
        elif propertytag.attrib.get('name') == LogKeepFileName:
            tmpStr = propertytag.attrib.get('value')
            tmpStrSub = re.sub('.//log', '//log', tmpStr)
            if tmpStrSub:            
                # tag.attrib.set('value', tmpStrSub)
                propertytag.attrib.set('value', tmpStrSub)            

    servicexmltree.write(filenameTmp)

    servicesxmlf.close()
    configf.close()
    
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
    ''' Process argument passed by called and asign to global variables
    argv[0] this file name
    argv[1] Server Type: GATE GAME
    argv[2] ID
    '''

    global GServerType
    global GServerID
    
    if(sys.argv.__len__() != 3):
        GLogger.error('Parameters Count %d Is Not Correct' % sys.argv.__len__())
        exit(GERR_PARAMETER)

    if(sys.argv[1] == 'GATE'):
        GServerType = 'GATE'
    elif(sys.argv[1] == 'GAME'):
        GServerType = 'GAME'
    else:
        GLogger.error('First Parameter %s Is Not A Valid Server Type' % sys.argv[1])
        exit(GERR_PARAMETER)
        
    # for argeach in sys.argv:
    #     print 'argeach:', argeach
        
        
#os.system('start cmd')

# import subprocess
# subprocess.call(['notepad'])
    

def ProcessJar(filename = GConfigFile):
    ''' Process TmServices-0.1.0.jar '''
    os.system('jar xvf ' + GJarFileName + ' proxool.xml')

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
        # urlcontentrep1 = urlcontent.replace("localhost", db_ip)
        # urlcontentrep2 = urlcontentrep1.replace("tmdatacenter", db_name)
        # urlelem.text = urlcontentrep2

        # print urlcontentrep1, urlcontentrep2, urlelem.text

        urlcontentStrSubIP = re.sub('jdbc:mysql://[.\w]*?:3306', 'jdbc:mysql://' + db_ip + ':3306', urlcontent)
        urlcontentStrSubIPDBName = re.sub(':3306/[\w]*?\?', ':3306/' + db_name + '?', urlcontentStrSubIP)

        print urlcontentStrSubIPDBName

        urlelem.text = urlcontentStrSubIPDBName
        
    for tag in treeproxool.getiterator('property'):
        if tag.attrib.get('name') == "user":
            tag.set('value', db_user)
            
        elif tag.attrib.get('name') == "password":
            tag.set('value', db_passwd)

    filenameTmp = "proxool.xml.tmp.xml"
    treeproxool.write(filenameTmp)

    fproxool.close()
    os.system('mv ' + filenameTmp + ' proxool.xml')
    os.system('jar uvf ' + GJarFileName + ' proxool.xml')
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
    initialize()
    ProcessArg()
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
    # PSX(servicesxmlFile, GConfigFile)
    # PSX()
    # PDSA()

    
    GLogger.info('test')
    # exit with return value: 0 is success other is failed
    exit(0)     
