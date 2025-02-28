/*
Підійшли до річки англієць, француз та індіанець, кожен зі своєю 
дружиною. Всім потрібно переправитися на інший берег. У їх 
розпорядженні знаходиться один човен без весляра, здатний вмістити двох. 
Але виявилось, що жодна з дружин не бажає переправлятися в човні з чужим 
чоловіком або залишатися на березі в чоловічому товаристві без свого 
чоловіка. Як вони зуміли переправитися?
*/


% Score, Boat, M1, M2, M3, W1, W2, W3
initial_state(100, left, state([left, left, left], [left, left, left])).
final_state(0, right, state([right, right, right], [right, right, right])).

main(Moves):-
    initial_state(InitScore, InitBoatSide, InitState),
    hill_climb(InitScore-InitState, InitBoatSide, [InitState], Moves),
    print_result(Moves, 1).

main(Moves, ListOfStates, StatesAmount):-
    initial_state(InitScore, InitBoatSide, InitState),
    hill_climb(InitScore-InitState, InitBoatSide, [InitState], Moves),
    findall(State, recorded(states_db, State), ListOfStates),
    length(ListOfStates, StatesAmount),
    print_result(Moves, 1).

hill_climb(StateComplex, _, _, []) :-
    final_state(FinalScore, _, FinalState),
    StateComplex = FinalScore-FinalState.
hill_climb(_-State, BoatSide, History, [NewMoveDescription | Moves]):-
    switch_boat_direction(BoatSide, BoatSideNew),
    get_possible_moves(State, BoatSide, BoatSideNew, PossibleMoves),
    member(CurrentHeuristicValue-NewMoveDescription-CurrentState, PossibleMoves),
    \+ member(CurrentState, History),
    legal(CurrentState),
    recorda(states_db, CurrentState),
    hill_climb(CurrentHeuristicValue-CurrentState, BoatSideNew, [CurrentState | History], Moves).

get_possible_moves(State, BoatSide, BoatSideNew, PossibleMoves) :-
    findall(HeuristicValue-MoveDescription-NewState, (
        move(State, NewState, BoatSide, BoatSideNew, MoveDescription),
        switch_state_to_int(NewState, IntState),
        calc_heuristic(MoveDescription, IntState, HeuristicValue),
        HeuristicValue < 100
        ), PossibleMovesNotSorted),
    sort(PossibleMovesNotSorted, PossibleMoves).


move(state([Side1, M2, M3], [Side1, W2, W3]), state([Side2, M2, M3], [Side2, W2, W3]), Side1, Side2, man-1+woman-1-to-Side2).
move(state([M1, Side1, M3], [W1, Side1, W3]), state([M1, Side2, M3], [W1, Side2, W3]), Side1, Side2, man-2+woman-2-to-Side2).
move(state([M1, M2, Side1], [W1, W2, Side1]), state([M1, M2, Side2], [W1, W2, Side2]), Side1, Side2, man-3+woman-3-to-Side2).

% man-man in the boat
move(state([Side1, Side1, M3], [W1, W2, W3]), state([Side2, Side2, M3], [W1, W2, W3]), Side1, Side2, man-1+man-2-to-Side2).
move(state([Side1, M2, Side1], [W1, W2, W3]), state([Side2, M2, Side2], [W1, W2, W3]), Side1, Side2, man-1+man-3-to-Side2).
move(state([M1, Side1, Side1], [W1, W2, W3]), state([M1, Side2, Side2], [W1, W2, W3]), Side1, Side2, man-2+man-3-to-Side2).

% woman-woman in the boat
move(state([M1, M2, M3], [Side1, Side1, W3]), state([M1, M2, M3], [Side2, Side2, W3]), Side1, Side2, woman-1+woman-2-to-Side2).
move(state([M1, M2, M3], [Side1, W2, Side1]), state([M1, M2, M3], [Side2, W2, Side2]), Side1, Side2, woman-1+woman-3-to-Side2).
move(state([M1, M2, M3], [W1, Side1, Side1]), state([M1, M2, M3], [W1, Side2, Side2]), Side1, Side2, woman-2+woman-3-to-Side2).

% One passanger in the boat
move(state([Side1, M2, M3], [W1, W2, W3]), state([Side2, M2, M3], [W1, W2, W3]), Side1, Side2, man-1-to-Side2).
move(state([M1, Side1, M3], [W1, W2, W3]), state([M1, Side2, M3], [W1, W2, W3]), Side1, Side2, man-2-to-Side2).
move(state([M1, M2, Side1], [W1, W2, W3]), state([M1, M2, Side2], [W1, W2, W3]), Side1, Side2, man-3-to-Side2).
move(state([M1, M2, M3], [Side1, W2, W3]), state([M1, M2, M3], [Side2, W2, W3]), Side1, Side2, woman-1-to-Side2).
move(state([M1, M2, M3], [W1, Side1, W3]), state([M1, M2, M3], [W1, Side2, W3]), Side1, Side2, woman-2-to-Side2).
move(state([M1, M2, M3], [W1, W2, Side1]), state([M1, M2, M3], [W1, W2, Side2]), Side1, Side2, woman-3-to-Side2).


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


calc_heuristic(MoveDescription, IntState, HeuristicValue) :-
    heuristic_formula(MoveDescription, IntState, HeuristicValue), !.

heuristic_formula(_, state([M1, M2, M3], [W1, W2, W3]), 0) :-
    Sum is M1 + M2 + M3 + W1 + W2 + W3,
    Sum = 6.
heuristic_formula(_, state([M1, M2, M3], [W1, W2, W3]), Value) :-
    DistanceToGoal is M1 + M2 + M3 + W1 + W2 + W3,
    Progress is 6 - DistanceToGoal,
    Value is Progress * 10.

switch_state_to_int(State, Result) :-
    State = state([M1, M2, M3], [W1, W2, W3]),
    side_to_int(M1, KN1), side_to_int(M2, KN2), side_to_int(M3, KN3),
    side_to_int(W1, SN1), side_to_int(W2, SN2), side_to_int(W3, SN3),
    Result = state([KN1, KN2, KN3], [SN1, SN2, SN3]).

% +String, -Int
side_to_int(left, 0).
side_to_int(right, 1).

% +From, -To
switch_boat_direction(left, right) :- !.
switch_boat_direction(right, left).

% +List, +StartNumber
print_result([], _).
print_result([Head | Tail], Number) :-
    format("~d) ~w", [Number, Head]),
    nl,
    NewNumber is Number + 1,
    print_result(Tail, NewNumber).
	
test_pm(State, OldBoat, Boat) :-
    get_possible_moves(State, OldBoat, Boat, PossibleMoves),
    print_result(PossibleMoves, 1).