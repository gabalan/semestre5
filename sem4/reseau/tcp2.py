import socket
import select
import threading

# Tcp Chat server
 
import socket
import select
import sys
 
CONNECTION_LIST = []
RECV_BUFFER = 4096
HOST = "0.0.0.0"
PORT = 5000
 
def broadcastToClients(sock, message):
    # Do not send the message to master socket and the client who has send us the message
    for socket in CONNECTION_LIST:
        if socket != server_socket and socket != sock:
            try:
                print(message)
                socket.send(message.encode('UTF-8'))
            except:
                # La ligne suivante permet d'afficher l'erreur
                # print("Unexpected error: "+sys.exc_info()[0])
                # En général, c'est le client qui n'est disponible
                # On ferme la connexion et on le supprime
            socket.close()
            CONNECTION_LIST.remove(socket)
 
 
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind((HOST, PORT))
server_socket.listen(10)
 
# On ajoute le serveur à la liste des connexions pour pouvoir "lire"
# la connexion d'un nouveau client
CONNECTION_LIST.append(server_socket)
 
print("Chat server started " + HOST + ":" + str(PORT))
 
while 1:
    try:
        # On recupère la liste des sockets dans lesquelles on peut lire dans read_sockets
        # écrire dans write_sockets...
        read_sockets, write_sockets, error_sockets = select.select(CONNECTION_LIST, [], [])
 
        for sock in read_sockets:
            # Si on peut lire dans celle du serveur c'est une nouvelle connexion
            if sock == server_socket:
                # On l'accepte et on ajoute la connexion à CONNECTION_LIST
                sockfd, addr = server_socket.accept()
                CONNECTION_LIST.append(sockfd)
                print("Client (" + addr[0] + ", " + str(addr[1]) + ") connected")
                # On envoie le message à tous les clients
                broadcastToClients(sockfd, "[" + addr[0] + ":" + str(addr[1]) + "] entered room\n")
 
            # Sinon c'est qu'un message à été reçu d'un client.
            else:
                try:
                    data = sock.recv(RECV_BUFFER).decode('UTF-8')
                    if data:
                        # Le message est envoyer à tous les clients.
                        # Le premiere paramètre est la socket dans laquelle le message a été reçu
                        #    pour ne pas lui retourner
                        broadcastToClients(sock, '<' + str(sock.getpeername()) + '> ' + data + '\n')
 
                except:
                    #La ligne suivante est utile pour savoir quelle erreur a été émise
                    # print("Unexpected error: " + sys.exc_info()[0])
                    broadcastToClients(sock, "Client [" + addr[0] + ":" + str(addr[1]) + "] is offline")
                    print("Client [" + addr[0] + ":" + str(addr[1]) + "] is offline")
                    sock.close()
                    CONNECTION_LIST.remove(sock)
                    continue
    except KeyboardInterrupt:
        print("Stop.\n")
        break
 
server_socket.close()
