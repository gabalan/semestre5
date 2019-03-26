#moyenne = esperance
#E(X)=\somme x*P(x)
# dessin.dessin_va([probaTM2.tiragesRepetes(probaTM2.genere_de(6),100)])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(probaTM2.genere_de(6),100)])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(probaTM2.genere_de(6),10000)])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(lambda : probaTM2.premierSix(),100)])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(lambda : probaTM2.premierSix(),100)])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(lambda : probaTM2.premierSix(),n) for n in [100,10000]])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(lambda : probaTM2.premierSix(),n) for n in [100,10000]])
#>>> dessin.dessin_va([probaTM2.tiragesRepetes(lambda : probaTM2.premierSix(),n) for n in [100,10000]])



import dessin

from math import sqrt 
import probaTM2

def moyenne(d):
    s=0
    for key in d :
       s+=key*d[key]
    return s

def sommeListe(L):
    s=0
    for i in L:
        s += i
    return s

def variance(d):
    b=0
    s=0
    m=moyenne(d)
    for key in d :
        s+=key*key*d[key]
        b=s-m*m
    return b

def variance2(d):
    s=0
    m=moyenne(d)
    for key in d :
        s+=(key**2)*d[key]
    s-=m**2
    return s

def normalisation(d):
    m=moyenne(d)
    r=math.sqrt(variance(d))
    dicoY={}
    for key in d :
        dicoY[(key-m)/r] =d[key]
    return dicoY








