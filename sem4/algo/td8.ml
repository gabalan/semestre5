type 'a tree=Empty|Bin of 'a * 'a tree * 'a tree

type direction=Up|Down
type dyckword= direction list
let full t=
  let rec aux t acc=
    match t with
      Empty->acc
    |Bin(x,Empty,Empty)->(Down::acc)
    |Bin(x,g,d)->aux g (aux d (Up::acc) in aux t []
