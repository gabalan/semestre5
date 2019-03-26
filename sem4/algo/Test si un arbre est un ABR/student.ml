(*
    type 'a tree = Empty | Bin of 'a * 'a tree * 'a tree

    Écrire une fonction is_bst : ('a * int) tree -> bool qui teste si un arbre
    est un ABR, en temps O(n) où n est le nombre de noeuds.
    
    Les étiquettes des noeuds de t sont des couples (x, m) où x est la clé et m
    est sa multiplicité.
*)

(* Ne pas supprimer ni modifier la ligne suivante *)
open Asda

(* Remplacer la fonction suivante sans changer son nom *)
let is_bst t =
  let rec auxi t a1 a2=
  match t with
    Empty->true
  |Bin((x,m),g,d)->if a1<x && a2>x then auxi g a1 x && auxi d x a2
    else false
in auxi t min_int max_int;;
