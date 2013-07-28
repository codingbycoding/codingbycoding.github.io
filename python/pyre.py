

import re
m = re.match('f[12]oo', 'testf1oojackf2oo;')
if m is not None:
    print m.group()
else:
    print 'match failed.'


s = re.search('f[12]oo', 'testf1oojackf2oo;')
if s is not None:
    print s.group()
else:
    print 'search failed'





import re
m = re.match('f[12]oo', 'testf1oojackf2oo;')
if m is not None:
    print m.group()
else:
    print 'match failed.'


s = re.search('\w+@\w+\.com', 'abc@abc.com jack@jack.com;')
if s is not None:
    print s.group()
else:
    print 'search failed'




s = re.findall('\w+@\w+\.com', 'abc@abc.com jack@jack.com;')
if s is not None:
    print s
else:
    print 'findall failed'    

    
    
    

    
    
sub = re.sub('\w+@\w+\.com', 'abc#abc', 'abc@abc.com jack@jack.com;')
print sub


subn = re.subn('\w+@\w+\.com', 'abc#abc', 'abc@abc.com jack@jack.com;')
print subn



# regex default behavior is greedy
#change this behavior by operator ?
#.+?
s = re.search('.+', 'jackrose')
print s.group()


s = re.search('.+?', 'jackrose')
print s.group()
