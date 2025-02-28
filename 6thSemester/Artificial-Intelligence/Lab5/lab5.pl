%Replacer

list_edit(L) :-
    length(L, Length),
    Length > 3,
    replace_third_with_last(L, NewL),
    write(NewL).

replace_third_with_last([X,Y,_|T], [X,Y,Last|NewT]) :-
    last_element(T, Last),
    replace_third_with_last(T, NewT).
replace_third_with_last(L, L).

last_element([X], X).
last_element([_|T], X) :-
    last_element(T, X).



