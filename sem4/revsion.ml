let rec mult l a n=
  if n=0 then l
  else mult (a::l) a (n-1)
                 
let  repete l n=
  let rec aux l n acc=
    match l with
      []->List.rev(acc)
     |x::r-> aux r n (mult acc x n) in aux l n [];;
                                           
let _=repete ["a";"b";"c"] 3;;
