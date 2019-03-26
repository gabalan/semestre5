import random
import math





def lancer(n):
    mondict={}
    for i in range(n):
        l=random.randint(1,6)
        if not(l in mondict):
            mondict[l]=1
        else:
            mondict[l]=mondict[l]+1

    for i in  mondict:
        mondict[i]=mondict[i]/n
    return mondict

def premiersix():
    cpt=0
    while(random.randint(1,6)!=6):
        cpt=cpt+1
        random.randint(1,6)
    return cpt
    
def tirage
