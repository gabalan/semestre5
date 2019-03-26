type 'a planar_tree = Node of 'a * 'a planar_tree list
type 'a tree = Empty | Bin of 'a * 'a tree * 'a tree
 type direction = Up | Down
type dyckword = direction list
                          (*2*)
let sup l=List.rev(List.tl l);;
let  full_to_dyck t=
  let rec aux t acc=
    match t with
    |Empty-> acc
    |Bin(x,Empty,Empty)->Down::acc
    |Bin(x,g,d)->aux d (aux g (Up::acc)) in let l= aux t [] in sup l;;
let t=Bin(2,Bin(1,Bin(4,Empty,Empty),Bin(5,Empty,Empty)),Bin(3,Bin(10,Empty,Empty),Bin(8,Empty,Empty)));;
