%X,+FinalX+StepSize,+N
%EList
func(X,FX,H,N,L):-
    FXl is FX+H/100,
    equation(X,FXl,H,N,L).

%Equation

equation(X,FX,H,N,[R|Rs]):-
    X=<FX,
    Xn is X+H,
    left(X,LR),
    right(X,N,1,RR),
    R is LR/RR,
    equation(Xn,FX,H,N,Rs).

equation(X,FX,_,_,[]):-
    X>FX.


%Dependencies
left(X,R):-
    NewX is X + 1,
    sqrt(NewX,R).

right(_,0,R,R).
right(X,N,Acc,R):-
    N >= 1,
    NewAcc is Acc + N * sin(X),
    NewN is N - 1,
    right(X,NewN,NewAcc,R).
