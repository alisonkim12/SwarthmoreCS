(*
   A "higher-roder function" is a funtion that takes another fucnton as input
   
   A "first-class function" is a funtion that is treated as a value
   
*)

let inc1 (n : int ) : int = 
  n + 1
;;

let twice func arg = 
  func (func arg)
;; 

let k : int = twice (inc1) (5);;

(* Sample evaluation*)

let k : int = twice (inc1) (5);;

(* ==> *)

let k : int = twice inc1 (inc1 5);; 

let k : int = twice inc1 (5 + 1);; 

let k : int = twice inc1 6;; 



(* List combinators *)

let rec add_one_to_all (lst: int list ) : int list = 
  match lst with 
  | [] -> [] (*note: don't throw an exception*)
  | element :: rest -> 
    (element + 1) :: (add_one_to_all rest)
;; 

let incremented = add_one_to_all [4;5;6;7;8];;

let rec multiply_all_by_two (lst : int list) : int list = 
  match lst with 
  | [] -> [] (*note: don't throw an exception*)
  | element :: rest -> 
    (element * 2) :: (add_one_to_all rest)
;; 

let rec do_something_to_each_element (operation: 'a -> 'a) (lst : 'a list) : 'a list = 
  match lst with 
  | [] -> []
  | current :: rest -> 
    (operation current) :: (do_something_to_each_element operation rest)
 
;;

let some_list = do_something_to_each_element inc1 [4;5;6;7;8];;

let concatenate_exclaimation_point (s: string) : string = s ^ "!";;

let another_list = 
  do_something_to_each_element concatenate_exclaimation_point ["A"; "B"; "Fish"];;

;; 

let anonymous_example = 
  do_something_to_each_element 
    (fun n -> n + 7)
    [4;5;6;7;8]
;; 

let named_anonymous_function_question_mark = fun n -> n+1 ;;

(* Another combinator *)

let rec add_all_items (lst : int list) : int = 
  match lst with 
  | [] -> 0
  | element :: rest -> 
    element + add_all_items rest
;; 

let rec product_all_items  (lst : int list) : int = 
  match lst with 
  | [] -> 1 
  | element :: rest -> 
    element * add_all_items rest
;; 

let rec combine_all_items (operation: int -> int -> int) (base : int) (lst : int list) : int = 
  match lst with 
  | [] -> base 
  | element :: rest -> 
    operation element (combine_all_items operation base rest)

;; 

(* Partial application
   if I have a function that takes in several arguments, pass in the first few and it returns a function wanting the rest of the arguments 
  
  In other words: a function that takes in two parameters is equal to a function that takes in one parameter and the rest of the function 
    *)

let add_one_to_all lst = do_something_to_each_element (fun n -> n +1 ) lst;;

(*Another way to write what is above*)

let add_one_to_all = do_something_to_each_element (fun n -> n +1 );;




