open Asda
open View
open Rand

(*fonction auxiliaire sup_max qui prend en parametre un abre et retourne un triple (v,e,bst) où v est
la plus grande etiquette de l'abre passé en paramètre  et qui a pour multilicité e,bst est l'abre dans lequel le maximum v est
supprimé  *)
let rec sup_max t=
  match t with
  |Empty->(0,0,Empty)
  |Bin((x,m),g,Empty)-> if m=1 then  (x,m,g)else (x,m,Bin((x,m-1),g,Empty))
  |Bin((x,m),g,d)->let (v,e,a)=sup_max d in (v,e,Bin((x,m),g,a))

let rec bst_delete t x=
  match t with
    Empty->Empty
  |Bin((y,m),Empty,d) when y=x ->if m=1 then d else Bin((y,m-1),Empty,d)
  |Bin((y,m),g,d) when y=x-> if m=1 then let (v,e,a)=sup_max g in Bin((v,e),a,d) else Bin((y,m-1),a,d)
  |Bin((y,m),g,d)->if x<y then Bin((y,m),bst_delete g x,d) else Bin((y,m),g,bst_delete d x);;
let t=bst ()
let _=view_mult t
let p=Bin((5,2)
         ,Bin((3,3),Empty,Bin((4,1),Empty,Empty))
         ,Bin((10,1),Bin((6,4),Empty,Bin((9,1),Bin((7,5),Empty,Bin((8,2),Empty,Empty)),Empty)),Bin((14,2),Bin((11,1),Empty,Bin((13,3),Bin((12,3),Empty,Empty),Empty)),Empty)))
let x=view_mult(bst_delete p 10)
