#!/usr/bin/python
"""
this is launch Gate Grid Node DsAgent HPA determined by GServerType
"""


GServerType = ''
GServerID = ''
GVersion = ''


def ProcessArg():
    ''' Process argument passed by called and asign to global variables
    argv[0] this file name
    argv[1] Server Type: GATE GAME
    argv[2] ID

    '''
    
    for arg in sys.argv:
        print 'arg:', arg



if __name__ == '__main__':
    print '__main__'
    ProcessArg()
