type 'a tree=Empty | Bin of 'a*'a tree*'a tree
type 'a file=File of 'a file*'a file
open Asda
open View
open Rand




let dfs t=
  let rec aux pile acc=
    match pile with
          []->List.rev acc
    |p::pile'->match p with
      |Empty->aux pile' acc
      |Bin(x,g,d)->aux (g::(d::pile')) (x::acc) in aux [t] [];;

let bfs t=
  let rec aux pile acc=
    match pile with
          []->List.rev acc
    |p::pile'->match p with
      |Empty->aux pile' acc
      |Bin(x,g,d)->aux (g::d::pile') (x::acc) in aux [t] [];;

let t=Bin(5,Bin(4,Bin(1,Empty,Empty),Empty),Bin(10,Bin(7,Empty,Empty),Bin(42,Empty,Empty)));;
