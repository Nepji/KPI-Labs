
:- dynamic point/3.

% Point_Sign, Abscissa, Ordinate
db_filling :-
    point(_, _, _),
    !.

db_filling :-
    assert(point(a, 1, 2)),
    assert(point(b, 6, 2)),
    assert(point(c, 3, 6)),
    assert(point(d, 5, 6)).

find_trapezoids(Trapezoids) :-
    db_filling,
    findall(T, trapezoid(T), Trapezoids).

trapezoid([P1, P2, P3, P4]) :-
    point(P1, X1, Y1), %A
    point(P2, X2, Y2), %B
    point(P3, X3, Y3), %C
    point(P4, X4, Y4), %D
    P1 \= P2, P1 \= P3, P1 \= P4,
    P2 \= P3, P2 \= P4,
    P3 \= P4,
    M1 is (Y2 - Y1) / (X2 - X1),
    M2 is (Y4 - Y3)/(X4 - X3),
    M1 =:= M2,
    M3 is (Y3 - Y1)/(X3 - X1),
    M4 is (Y4 - Y2)/(X4 - X2),
    M3 =\= M4.
