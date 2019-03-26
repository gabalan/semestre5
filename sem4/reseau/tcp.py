import socket
import select
import threading

s=socket.socket(socket.AF_INET6,socket.SOCK_STREAM)
s.bind(('',7777))
s.listen(1)
while 1:
    con,addr = s.accept()
    print('connect',addr)
    while 1:
        data = con.recv(1500)
        msg = con.send(data)
        if not msg:
            break
con.close()
s.close()

