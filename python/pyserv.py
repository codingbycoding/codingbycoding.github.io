import socket
import time

sshost = '127.0.0.1'
ssport = 8888
ssaddr = (sshost, ssport)
listennum = 5
recvbuf = 1024

print 'This is Serv...'
ss = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ss.bind(ssaddr)
ss.listen(listennum) 

# while True:
reqnum = 0
while reqnum < 2:    
    cs, csaddr = ss.accept()
    recvdata = cs.recv(recvbuf)
    print 'recv from client: %s' % recvdata
    
    cs.send('request recv at: %s' % (time.ctime()))
    cs.close()
    reqnum += 1

    
ss.close()
