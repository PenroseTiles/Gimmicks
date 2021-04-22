datatype 'a seq =  Nil | Cons of ('a * (unit -> 'a seq))
signature SEQUENCE =
sig
    val hd : 'a seq  -> 'a
    val tl : 'a seq -> 'a seq
    val cons : 'a * 'a seq -> 'a seq
    val zip : 'a seq * 'b seq -> ('a * 'b) seq
    val from : int -> int seq
    val take : 'a seq * int -> 'a list
end


structure Sequence :>SEQUENCE=
struct
exception Empty
exception UnequalLengthArgs

fun hd Nil = raise Empty
  | hd (Cons(x, f)) = x
fun tl Nil = raise Empty
  | tl (Cons(x,f)) = (f())
fun cons (x, seq) = Cons(x, fn () => seq)
fun zip (Nil, Nil) = Nil
  | zip (Cons(x,f), Cons(y,g)) = Cons((x,y), fn () =>zip(f(), g()))
  | zip _ = raise UnequalLengthArgs
fun from (k:int) = Cons(k, fn()=>from(k+1))
fun take (s, 0) = []
  | take (Nil, idx) = raise Empty
  | take (Cons(x, f), idx) = x::take(f(), idx-1)
end
