from random import *

def SequencesBinaire(n):
    if n == 0 :
        return [[]]
    else :
        l=[]
        for i in (SequencesBinaire(n-1)) :
            l+=[i+[1],i+[0]]
    return l 


def SequenceBinaireVersParties (s) :
    k=[]
    for i in range(len(s)):
        if s[i]==1:
            k.append(i+1)
            
    return tuple(k)
def Parties(n,k):
    L=[]
    for seq in SequencesBinaire(n):
        t = SequenceBinaireVersParties(seq)
        if len(t)==k:
            L+=[t]
    return L
    
    

def PremierPartie(n,k):
    l=[]
    for i in  range(k) :
        l.append(i+1)
    return tuple(l)

def PartieSuivant(n,p):
    k=len(p)
    i=k-1
    if p[i]<n :
        p[i]+=1
        return p
    else :
        i-=1
        while p[i]==p[i+1]-1 :
            i-=1
        if i<0:
            return False
            # tester si p n'est pas la derniere
        p[i]+=1
        i+=1
        while i <k :
            p[i]=p[i-1]+1
            i+=1
        return p

def ToutesParties(n,k):
    L=[]
    p=list(PremierPartie(n,k))
    while p!=False:
        L.append(tuple(p))
        p=PartieSuivant(n,p)
    return L

#Exercice 5-2


def melange(L) :
    n=len(L)
    for i in range(1,n) :

        pos = randint(0,i)
        if pos != i:
            (L[pos],L[i])=(L[i],L[pos])
    return L
# TM6


def binomiale(n,p):
    d=dict()
    d[0]=(1-p)**n
    
    for k in range(0,n):
        d[k+1]=d[k]*(n-k)*p/((k+1)*(1-p))
    
    return d

def loi_difference_entreB_A_c (n,p,q):
        A=binomiale(n,p)
        B=binomiale(n,q)
        C=dict()
        #k positif
        for k in range(0 , n+1):
            C[k]=0
            for i in range(0 , n-k+1) :
                C[k]+=B[k+i]*A[i]
        for k in range (-n,0):
            C[k]=0
            for i in range(-k,n+1):
                C[k]+=B[k+i]*A[i]
        return C
                


    
        
    
    
    
    
    
    
            

            

    
    
    
    
    


        
    
    
            
#[1,1,1,0,0,0,0] ->  (1,2,3)
#[0,1,0,0,0,0,1] ->  (2,7)
            
            
    
    
