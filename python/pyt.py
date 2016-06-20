import re

with open('test.cfg', 'r') as f:
    for eachLine in f: #f.readline():
        if eachLine == '\n':
            print 'newline find'
        
        print 'eachLine: %s' % eachLine
        m = re.search('DcAddress[ ]*=[ ]*[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}[ ]*\n', eachLine)
        if m:
            print 'search found!!!'
            DcAddress = '172.17.189.10'
            strDcAddress = 'DcAddress=' + DcAddress + '\n'
            m.
