
% Question ?Name1,?Name2
can_fight(X,Y):-
    showMatch(X,WeightCategory,SportCategory),
    showMatch(Y,WeightCategory,SportCategory),
    X\==Y.

% All pairs
show_all_pairs :-
    findall((X, Y), (can_fight(X, Y), \+ member((Y,X),Pairs)), Pairs),

    display_pairs(Pairs).

%loop
display_pairs([]).
display_pairs([(X,Y)|Rest]):-

    write(X), write(' '), write(Y), nl,
    display_pairs(Rest).

% Sportsman, Weight Category, Sport Category
showMatch(tolik,50,first).
showMatch(stepan,60,first).
showMatch(valera,50,second).
showMatch(vladislave,50,first).
showMatch(pavel,60,second).
showMatch(usik,60,second).
showMatch(shadowfighter,60,second).
showMatch(tempone,50,second).
showMatch(king,100,master).


