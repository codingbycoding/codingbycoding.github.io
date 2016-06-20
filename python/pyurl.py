import urllib

def main():
    # f = urllib.open('http://www.baidu.com')
    filename, hdr = urllib.urlretrieve('http://www.baidu.com')
    print 'filename: \n%s \nhdr: \n%s' % (filename, hdr)
    



    
if __name__ == '__main__':
    main()
