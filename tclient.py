#!/usr/bin/env python 
from socket import *
import time
from SocketServer import ThreadingTCPServer, BaseRequestHandler 
import struct
def tcpset(top):
    HOST = '127.0.0.1'
    PORT = 8010
    BUFSIZE = 1024
    ADDR = (HOST, PORT)
    tcpClientSock = socket(AF_INET, SOCK_STREAM)
    str = 'Try to connect Task server(%s:%d)...' % (HOST,PORT)
    print str
    while True:
        try:
            tcpClientSock.connect(ADDR)
        except:
            print('Unable to connect Task server,try again!...')
            time.sleep(1)
            continue
        break
    str = 'Connect to Task server(%s:%d)' % (HOST,PORT)
    print str
    while True:
        data = tcpClientSock.recv(BUFSIZE)
        A = struct.unpack("4shh",data)
        print A
        cmd = A[2]
        if cmd == 4:
            top.container_float2float_0.Setparam('TTC_Param.xml','container_float2float_0')
    tcpClientSock.close()
