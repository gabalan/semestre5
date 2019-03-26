def bfs(G,s) :
    couleur=dict()
    for x in G : couleur[x]="blanc"
    P=dict()
    P[s]=None
    couleur[s]="gris"
    Q=[s]
    while Q :
        u=Q[0]
        for v in G[u] :
            if couleur[v]=="blanc" :
                P[v]=u
                couleur[v]="gris"
                Q.append(v)
        Q.pop(0)
        couleur[u]="noir"
    return P
