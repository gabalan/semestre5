type 'a tree = Empty | Bin of 'a * 'a tree * 'a tree

let rec btree_size p t=
  match t with
   Empty-> 0
  |Bin(x,Empty,Empty)->if (p x) then 1
                                       else 0
   |Bin(x,g,d)->(if (p x) then 1 else 0)+(btree_size p  g) +( btree_size p  d)
                   
   
  let rec btree_height1 p  t=
    match t with
      Empty-> (-1)
  
    |Bin(x,g,d)-> if (p x) then 1 + max ( btree_height1 p g)( btree_height1 p d)
                                        else -1
                                         

  let rec verif p t=
    match t with
      Empty-> true
    |Bin(x,g,d)-> (p x)||  verif p g || verif p d
  let rec btree_height1 p  t=
  
    match t with
    Empty-> (-1)
  |Bin(x,Empty,Empty)->if (p x) then 0 else -1
  |Bin(x,g,Empty)  ->if not (p x) then -1
                    else 1+ btree_height1 p g
  |Bin(x,Empty,d)  ->if not (p x) then -1
                    else 1+ btree_height1 p d
  |Bin(x,g,d)-> if not ( p x) then
                  -1 else 1 + max ( btree_height1 p g)( btree_height1 p d)
                                 

 let rec btree_height2 p  t=
    match t with
    Empty-> (-1)
     |Bin(x,Empty,Empty)->if (p x) then 0 else -1
   |Bin(x,g,d)-> if ( p x) then  1 + max ( btree_height g)( btree_height d)
                                         else -1

 
let rec feuilles p t=
    match t with
    Empty-> 0
    |Bin(x,Empty,Empty)->if (p x)then  1 else 0
    |Bin(x,g,d)-> (feuilles p g )+(feuilles p  d)


let rec arity1 p t=
    match t with
    Empty->0
   |Bin(x,Empty,Empty)->0
   |Bin(x,Empty,d)->( if ( p x) then 1 else 0)+arity1 p d
   |Bin(x,g,Empty)->( if ( p x) then 1 else 0)+arity1 p g
   |Bin(x,g,d)->arity1 p g +arity1 p d

let rec arity2 p  t=
    match t with
    |Empty->0
    |Bin(x,Empty,Empty)->0
    |Bin(x,Empty,d)->arity2 p d
    |Bin(x,g,Empty)->arity2 p g
    |Bin(x,g,d)->( if ( p x) then 1 else 0)+ arity2 p g +arity2 p d
    
let rec parameters_gen p t=
    match t with
    |Empty->(0,0,0,0,(-1),(-1))
    |Bin(x,g,d)->(btree_size p t,feuilles p  t,arity1 p  t ,arity2 p  t,btree_height1 p t,btree_height2  p t)

let t=Bin (69, Empty, Bin (1, Empty, Empty))
          let p=(fun x -> x mod 3 = 0)
                   (*let _ = parameters_gen (fun x -> x mod 3 = 0) (Bin (79, Bin (3, Empty, Empty), Bin (0, Empty, Empty))*)
