#!/usr/local/bin/python3
import tkinter

def dictToList(dict):
    return [(k,v) for k,v in dict.items()]

def dessiner_fonctions_de_repartition(fonctions_de_repartition,xmin,xmax):
    fonctions_de_repartition=[dictToList(u) for u in fonctions_de_repartition]
    canvas_width = 500
    canvas_height = 500
    xscale = xmax - xmin
    yscale = 1.1
    fenetre = tkinter.Tk()
    canvas = tkinter.Canvas(width=canvas_width,height=canvas_height)
    canvas.pack()
    def map_point_into_canvas(a_point):
        return ((a_point[0]-xmin)/xscale*canvas_width,(1.05-a_point[1])/yscale*canvas_height)
    def dessiner_une_fonction_de_repartition(valeurs_aux_atomes,couleur_fonction,couleur_atome):
        valeurs_aux_atomes.sort(key=lambda p:p[0]) # ensure increasing values
        first_point = (min(valeurs_aux_atomes[0][0],xmin),0)
        last_point = (max(valeurs_aux_atomes[-1][0],xmax),1)
        valeurs_aux_atomes = [first_point] + valeurs_aux_atomes + [last_point]
        for i in range(1,len(valeurs_aux_atomes)):
            (xa,ya) = map_point_into_canvas(valeurs_aux_atomes[i-1])
            (xb,yb) = map_point_into_canvas(valeurs_aux_atomes[i])
            canvas.create_line(xa,ya,xb,ya,fill=couleur_fonction,width=2)
            canvas.create_line(xb,ya,xb,yb,fill=couleur_atome,width=1,dash=(3,5))
            canvas.create_text(xb,canvas_height*0.98,text=str(int(valeurs_aux_atomes[i][0])),fill=couleur_atome)
    couleur_des_fonctions = ['green','orange','magenta'] # allonger la liste si besoin
    for i in range(len(fonctions_de_repartition)):
        dessiner_une_fonction_de_repartition(fonctions_de_repartition[i],couleur_des_fonctions[i%len(couleur_des_fonctions)],'blue')
    for i in range(0,11):
        (xl,yl) = map_point_into_canvas((xmin,i/10))
        (xr,yr) = map_point_into_canvas((xmax,i/10))
        canvas.create_line(xl,yl,xr,yr,fill='red',dash=(2,2))
        canvas.create_text(xl+30,yl,text=str(i*10)+'%')
    fenetre.mainloop()
