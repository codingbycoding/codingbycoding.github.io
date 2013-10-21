configFile = 'config.xml'
JarFileName = 'TmServices-0.1.0.jar'


def paramInit(filename = configFile):
    global JarFileName
    
    

    
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
        db_ip = tag.attrib.get('IP')
        db_name = tag.attrib.get('DATABASE')
        db_user = tag.attrib.get('USERNAME')
        db_passwd = tag.attrib.get('PASSWD')


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
    urlcontent = tree.findtext('driver-url')
    if urlcontent:
        print urlcontent


if __name__ == '__main__':
    print '__main__'
    ProcessJar()
