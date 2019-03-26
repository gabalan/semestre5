# -*- coding: Utf-8 -*
# Author: aurelien.esnard@u-bordeaux.fr

from model import *
import socket
import select

################################################################################
#                          NETWORK SERVER CONTROLLER                           #
################################################################################

class NetworkServerController:

    def __init__(self, model, port):
        self.model = model
        self.port = port
        self.ddd= self.model.map.filename
        # ...
        self.serveur = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
        self.serveur.bind(('',port))
        self.serveur.listen(5)
        self.liste=[]
        self.filename=''
    # time event
    def tick(self, dt):
        while (True):
            self.filename=self.model.load(filename)
            rliste , wlist , xlist = select.select(self.liste+[self.serveur],[],[])
            for s in rliste:
                if (s==self.serveur):
                    newsocket, addr = s.accept()
                    self.liste.append(newsocket)
                    print( "nouvelle connexion  de")
                else:
                    data = s.recv(1500)
                    for d in self.liste:
                        d.send(data)
                        if (len(data) ==0):
                            d.close()
                            self.liste.remove(d)
        self.socket.close()
        # ...
        return True

################################################################################
#                          NETWORK CLIENT CONTROLLER                           #
################################################################################

class NetworkClientController:

    def __init__(self, model, host, port, nickname):
        self.model = model
        self.host = host
        self.port = port
        self.nickname = nickname
        self.socket=socket.socket(socket.AF_INET,socket.SOCK_STREAM)
        print("la map",self.model)
        try:
            self.socket.connect((host,port))
        except:
            print( "la connection a echoué")
            sys.exit()
        print ("connection ok avec",nickname)
        self.msg=self.socket.recv(1500)
        while 1:
            if self.msg.upper()=="FIN" or self.msg=="":
                print ("D",self.msg)
                self.msgclient=raw_input("C> ")
                self.socket.send(self.msg.client)
                self.msg=self.socket.recv(1500)
        print ("connection de ",nickname,"fermée")
        self.socket.close()
        # ...

    # keyboard events

    def keyboard_quit(self):
        print("=> event \"quit\"")
        return False

    def keyboard_move_character(self, direction):
        print("=> event \"keyboard move direction\" {}".format(DIRECTIONS_STR[direction]))
        # ...
        return True

    def keyboard_drop_bomb(self):
        print("=> event \"keyboard drop bomb\"")
        # ...
        return True

    # time event

    def tick(self, dt):
        # ...
        return True
