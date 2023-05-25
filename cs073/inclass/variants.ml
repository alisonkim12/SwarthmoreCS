(* Variant Type *)

(* day_of_week is an "enum" *)

type day_of_week =
  | Sunday
  | Monday
  | Tuesday

let is_weekend (d: day_of_week) : bool =
  match d with
    Sunday -> true
    Monday -> false
    Tuesday -> false

  ;;
