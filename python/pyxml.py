#!/usr/bin/python

from xml.etree import ElementTree



if __name__ == '__main__':
    print '__main__'
    with open('config.xml', 'rt') as f:
        tree = ElementTree.parse(f)

    # for node in tree.iter():
    for node in tree.getiterator('GAME'):        
        #print node.tag
        inip = node.attrib.get('INIP')
        if inip:
            print inip
