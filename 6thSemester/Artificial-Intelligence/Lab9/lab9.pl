pz_data([person(N1,C1,1),person(N2,C2,2),person(N3,C3,3),person(N4,C4,4)]).

%FULL

next_to(A,B,[A,B,_,_]).
next_to(A,B,[_,A,B,_]).
next_to(A,B,[_,_,A,B]).

p_name(person(Name,_,_),Name).
p_work(person(_,Work,_),Work).
p_house(person(_,_,House),House).

solve(T):-
    pz_data(T),
    next_to(K11,K12,T),
    p_work(K11,artist),
    p_work(K12,trener),
    next_to(K21,K11,T),
    p_work(K21,doctor),
    next_to(K31,K21,T),
    p_work(K31,jagermeister),
    \+ next_to(K12,K31,T),
    next_to(K41,K11,T),
    p_name(K41,semen),
    p_name(K31,roman),
    next_to(K41,K61,T),
    p_name(K61,mikola),
    \+ next_to(K31,K12,T),
    p_name(K12,artur).
