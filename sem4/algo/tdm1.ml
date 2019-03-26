(*2.3*)

let rec fib n=
  if n<=0 then 0
  else if n=1 then 1
  else fib(n-1)+fib(n-2);;

  
let timer n=
let temps_avant_execution =Sys.time() in let = fib n in
let temps_apres_execution= Sys.time() in
in temps_avant_execution-.temps_apres_exection;;
   

let rec  insert l x = 
    match l with
    |[]->[x]
    |y::r->if x<y then x::l
           else  y::insert r x


let  repartition l=
  let rec aux l acc1 acc2=
  match l with
  |[]->(acc1,acc2)
  |x::[]->(acc1@[x],acc2)
  |x::y::r->aux r (acc1@[x]) (acc2@[y]) in aux l [] [];; 
                  
let rec merge l1 l2 = 
    match (l1,l2) with
    |[],_->l2
     |_,[]->l1
    |x::r,y::z->if (x<y) then x::merge r l2
    else y::merge l1 z;;

let rec merge_sort l =
  match l with
  |[]->[]
  |x::[]->l
  |x::r-> let (l1,l2)=repartition l in merge (merge_sort (l1)) (merge_sort (l2));;
