let rec btree_size t=
  match t with
   Empty-> 0
   |Bin(x,Empty,Empty)->1
   |Bin(x,g,d)->1+(btree_size g) +( btree_size d)
   
   
  let rec btree_height t=
    match t with
    Empty-> (-1)
   |Bin(x,Empty,Empty)->0
   |Bin(x,g,d)->1+ max ( btree_height g)( btree_height d)

 

let rec feuilles t=
    match t with
    Empty-> 0
    |Bin(x,Empty,Empty)-> 1
    |Bin(x,g,d)-> (feuilles g )+(feuilles d)


let rec arity1 t=
    match t with
    Empty->0
   |Bin(x,Empty,Empty)->0
   |Bin(x,Empty,d)->1+arity1 d
   |Bin(x,g,Empty)->1+arity1 g
   |Bin(x,g,d)->arity1 g +arity1 d

let rec arity2 t=
    match t with
    |Empty->0
    |Bin(x,Empty,Empty)->0
    |Bin(x,Empty,d)->arity2 d
    |Bin(x,g,Empty)->arity2 g
    |Bin(x,g,d)->1+ arity2 g +arity2 d
    
let rec parameters t=
    match t with
    |Empty->(0,0,0,0,(-1))
    |Bin(x,g,d)->(btree_size t,feuilles t,arity1 t ,arity2 t,btree_height t)
