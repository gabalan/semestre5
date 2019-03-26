import random
import math
def premiersix():
    cpt=0
    while(random.randint(1,6)!=6):
        cpt=cpt+1
        random.randint(1,6)
    return cpt
def tiragesRepetes(modele,n):
    mondict={}
    for i in range(n):
        l=modele()
        if not(l in mondict):
            mondict[l]=1
        else:
            mondict[l]=mondict[l]+1

    for i in  mondict:
        mondict[i]=mondict[i]/n
    return mondict
        
def genere_de2(d):
    def toto():
        return random.randint(1,d)
    return toto

def genere_de(d):
    return lambda : random.randint(1,d)


def somme(k,d):
    compt=0
    for i in range(k):
        de=genere_de(d)
        val_de=de()
        compt=compt+val_de
    return compt


def tiragerep(d,v):
    compt=1
    de=genere_de(d)
    val_de=de()

    while(val_de!=v):
        compt=compt+1
        de=genere_de(d)
        val_de=de()
    return compt
    
