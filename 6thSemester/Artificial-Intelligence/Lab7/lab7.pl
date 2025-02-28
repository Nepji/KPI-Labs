matrix_data(1,
[[2,1,1,1,5],
 [1,2,1,4,1],
 [1,1,3,1,1],
 [1,1,1,1,1],
 [1,1,1,1,1]]
).

sum_half_diagonals_above_center(MatrixID, Sum) :-
    matrix_data(MatrixID, Array),
    length(Array, Size),
    sum_half_diagonals_above_center(Array, 0, Size, 0, Sum).

sum_half_diagonals_above_center([], _, _, Sum, Sum).

sum_half_diagonals_above_center([Row|Rest], C, Size, CurrentSum, Sum) :-
    C < Size // 2,
    nth0(C, Row, FirstElem),
    SecondPos is Size - C - 1,
    nth0(SecondPos, Row, SecondElem),
    Elem is FirstElem + SecondElem,
    NextC is C + 1,
    NewSum is CurrentSum + Elem,
    sum_half_diagonals_above_center(Rest, NextC, Size, NewSum, Sum).

sum_half_diagonals_above_center([_|Rest], C, Size, CurrentSum, Sum) :-
    C >= Size // 2,
    NextC is C + 1,
    sum_half_diagonals_above_center(Rest, NextC, Size, CurrentSum, Sum).
