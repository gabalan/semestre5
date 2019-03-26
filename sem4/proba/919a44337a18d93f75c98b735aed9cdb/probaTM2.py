from random import *
def lancers(n):
    d={}
    
    for i in range(n):
        a=randint(1,6)
        if a in d.keys():
            d[a]+=1
        else :
                d[a]=1
                
    for j in d.keys() :
        d[j]=d[j]/n
    return d

def premierSix() :
    
    d={}
    a=randint(1,6)
    cpt=1
    while a!=6:
            cpt+=1
            a=randint(1,6)
    return cpt 

def tirageRepetePremierSix(n) :
    d={}
    for i in range (n) :

        a=premierSix()
        if a in d :
            d[a]+=1
        else :
            d[a]=1
    for a in d.keys() :
        d[a]=(d[a]*1.0)/n
                
        
        
    return d

def tiragesRepetes(modele,n):
    d=dict()
    for i in range(n):
        a=modele()
        if a in d.keys():
            d[a]+=1
        else :
            d[a]=1
    for j in d.keys() :
        d[j]=(d[j]*1.0)/n

    return d 


def genere_de(d):
    def De():
        return randint(1,d)
    
    return De 

def simu_generique1(L) :

    def toto () :
        x=random()
        s=0
        for i in range(len(L)):
            s+=L[i]
            if x<s :
                return i 
        return i
        
            
    return toto
def simu_generique2(L):
    def toto1 () :
        x=random()
        i=0
        s=0
        for p in L :
            s+=p
            if x<s :
                return i
            i+=1
        return i-1
    return toto1

def simu_generique_dict (D) :
    def toto_dict():
        x=random()
        s=0
        for k in D:
            s+=D[k]
            if x<s :
                return k
        return k #au cas d'erreur d'arrondis
    return toto_dict 


def sommes_de_des (k,d):
    def simulateur () :
        compteur=0
        for i in range(k) :
            compteur+=genere_de(d)()
        return compteur
    return simulateur 
        
def tirage(d,v):
    def simulateur () :
        cpt=1
        x= genere_de(d)
        
        while x() != v :
            cpt+=1
            
        return cpt
    return simulateur
def valeurs (k,d) :
    def simulateur () :
        l=[]
        cpt=0
        x=genere_de(d)
        for i in range(k):
            l.append(x())
        return tuple(l)
    return simulateur

def frequenceVers_distribution (freq) :
    Keys=list(freq.keys())
    Keys.sort ()
    somme_partielle=0
    distribution=dict()
    for i in Keys :
           somme_partielle+=freq[i]
           distribution[i]=somme_partielle
    return distribution 

        
        
            
            

            
            
        
    

            
        
    
    
