%Equation
func(X,K,R):-
    K > X,
    R is K.

func(X,K,R):-
    X > K,
    mult(X,K,1,R).

%Dependencies
mult(X,K,Acc,R):-
    K >=1 ,
    NewAcc is Acc * K * X,
    NewK is K - 1,
    mult(X,NewK,NewAcc,R).

mult(_, 0, R, R).
