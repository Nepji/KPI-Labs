/*
Підійшли до річки англієць, француз та індіанець, кожен зі своєю 
дружиною. Всім потрібно переправитися на інший берег. У їх 
розпорядженні знаходиться один човен без весляра, здатний вмістити двох. 
Але виявилось, що жодна з дружин не бажає переправлятися в човні з чужим 
чоловіком або залишатися на березі в чоловічому товаристві без свого 
чоловіка. Як вони зуміли переправитися?
*/


% Boat, M1, M2, M3, W1, W2, W3
initial_state(left, state([left, left, left], [left, left, left])).
final_state(right, state([right, right, right], [right, right, right])).

% man-woman in the boat
move(state([Side1, M2, M3], [Side1, W2, W3]), state([Side2, M2, M3], [Side2, W2, W3]), Side1, Side2, man1+woman1-to-Side2).
move(state([M1, Side1, M3], [W1, Side1, W3]), state([M1, Side2, M3], [W1, Side2, W3]), Side1, Side2, man2+woman2-to-Side2).
move(state([M1, M2, Side1], [W1, W2, Side1]), state([M1, M2, Side2], [W1, W2, Side2]), Side1, Side2, man3+woman3-to-Side2).

% man-man in the boat
move(state([Side1, Side1, M3], [W1, W2, W3]), state([Side2, Side2, M3], [W1, W2, W3]), Side1, Side2, man1+man2-to-Side2).
move(state([Side1, M2, Side1], [W1, W2, W3]), state([Side2, M2, Side2], [W1, W2, W3]), Side1, Side2, man1+man3-to-Side2).
move(state([M1, Side1, Side1], [W1, W2, W3]), state([M1, Side2, Side2], [W1, W2, W3]), Side1, Side2, man2+man3-to-Side2).

% woman-woman in the boat
move(state([M1, M2, M3], [Side1, Side1, W3]), state([M1, M2, M3], [Side2, Side2, W3]), Side1, Side2, woman1+woman2-to-Side2).
move(state([M1, M2, M3], [Side1, W2, Side1]), state([M1, M2, M3], [Side2, W2, Side2]), Side1, Side2, woman1+woman3-to-Side2).
move(state([M1, M2, M3], [W1, Side1, Side1]), state([M1, M2, M3], [W1, Side2, Side2]), Side1, Side2, woman2+woman3-to-Side2).

% One passanger in the boat
move(state([Side1, M2, M3], [W1, W2, W3]), state([Side2, M2, M3], [W1, W2, W3]), Side1, Side2, man1-to-Side2).
move(state([M1, Side1, M3], [W1, W2, W3]), state([M1, Side2, M3], [W1, W2, W3]), Side1, Side2, man2-to-Side2).
move(state([M1, M2, Side1], [W1, W2, W3]), state([M1, M2, Side2], [W1, W2, W3]), Side1, Side2, man3-to-Side2).
move(state([M1, M2, M3], [Side1, W2, W3]), state([M1, M2, M3], [Side2, W2, W3]), Side1, Side2, woman1-to-Side2).
move(state([M1, M2, M3], [W1, Side1, W3]), state([M1, M2, M3], [W1, Side2, W3]), Side1, Side2, woman2-to-Side2).
move(state([M1, M2, M3], [W1, W2, Side1]), state([M1, M2, M3], [W1, W2, Side2]), Side1, Side2, woman3-to-Side2).

%%%%%%%%%%%%%%%%%% Checking for legality  %%%%%%%%%%%%%%%%%%
% +State
legal(state([M1, M2, _], [W1, _, _])) :-
    W1 \= M1,
    W1 = M2, !, fail.
legal(state([M1, _, M3], [W1, _, _])) :-
    W1 \= M1,
    W1 = M3, !, fail.
legal(state([M1, M2, _], [_, W2, _])) :-
    W2 \= M2,
    W2 = M1, !, fail.
legal(state([_, M2, M3], [_, W2, _])) :-
    W2 \= M2,
    W2 = M3, !, fail.
legal(state([M1, _, M3], [_, _, W3])) :-
    W3 \= M3,
    W3 = M1, !, fail.
legal(state([_, M2, M3], [_, _, W3])) :-
    W3 \= M3,
    W3 = M2, !, fail.
legal(_).

update_boat(left, right) :- !.
update_boat(right, left).

main(Moves) :-
    initial_state(BoatInitSide, state([M1, M2, M3], [W1, W2, W3])),
    dfs(state([M1, M2, M3], [W1, W2, W3]), BoatInitSide, [state([M1, M2, M3], [W1, W2, W3])], Moves),
    print_result(Moves, 1),
    statistics, nl, nl.

dfs(State, BoatSide, _, []):-
    final_state(BoatSide, State).
dfs(State, BoatSide, History, [Move | Moves]):-
    update_boat(BoatSide, BoatSide2),
    move(State, State2, BoatSide, BoatSide2, Move),
    \+ member(State2, History),
    legal(State2),
    dfs(State2, BoatSide2, [State2 | History], Moves).

%--------------------------------------------------------------------------------
% Auxiliary predicates
print_result([], _).
print_result([Head | Tail], Number) :-
    format("~d) ~w", [Number, Head]),
    nl,
    NewNumber is Number + 1,
    print_result(Tail, NewNumber).