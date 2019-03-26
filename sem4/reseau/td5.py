import socket
import select
import threading


serveur=socket.socket(socket.AF_INET6,socket.SOCK_DGRAM)
serveur.bind(('',7777))
while 1:
    salut=serveur.recvfrom(1500)
    serveur.sendto(salut[0],salut[1])
