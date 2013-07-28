import socket


sshost = '127.0.0.1'
ssport = 8888
ssaddr = (sshost, ssport)

recvbuf = 1024

cs = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
#cs.bind(ssaddr)


print 'This is cli...'
#while Ture:
cs.connect(ssaddr)
cs.send('hello')
recvdata = cs.recv(recvbuf)

print 'recv from serv: %s' % recvdata

cs.close()
print 'cli exit...'
