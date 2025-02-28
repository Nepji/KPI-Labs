%ListLenght
list_length([], 0).
list_length([_|T], N) :-
    list_length(T, N1),
    N is N1 + 1.

%TakeFirstPart
take(0, _, []).
take(N, [H|T], [H|Result]) :-
    N > 0,
    N1 is N - 1,
    take(N1, T, Result).

%DropFirstHalf
drop(_, [], []).
drop(0, List, List).
drop(N, [_|Tail], Result) :-
    N > 0,
    N1 is N - 1,
    drop(N1, Tail, Result).

%mergeLists
merge_lists(List1, List2, Merged) :-
    list_length(List1, Len1),
    list_length(List2, Len2),
    Len1 mod 2 =:= 0,
    Len2 mod 2 =:= 0,
    HalfLen1 is Len1 // 2,
    HalfLen2 is Len2 // 2,
    drop(HalfLen1, List1, SecondHalf1),
    take(HalfLen2, List2, FirstHalf2),
    append(SecondHalf1, FirstHalf2, Merged).
