#!/usr/bin/env python

import socket
import time

ssdesthost = '192.168.86.198'
ssdestport = 80
ssdestaddr = (ssdesthost, ssdestport)

recvbuf = 1024


ssTCP = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
ssTCP.connect(ssdestaddr)
senddata = 'GET /message.html HTTP/1.1\r\nHost: 192.168.86.198\r\n\r\n';
ssTCP.send(senddata)
recvdata = ssTCP.recv(recvbuf)
print senddata
print recvdata
ssTCP.shutdown(socket.SHUT_WR)
ssTCP.close()




def main():
    print "main"


    
if __name__ == "__main__":
    main()
else:
    print "not main"
