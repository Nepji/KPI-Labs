
%Question
have_stepdaughter(X,Y):-
    is_equal_marriage(X,Y),
    is_equal_not_parrent(X,Y).

is_stepdaughter(X,Y):-
    is_equal_marriage(X,F),
    is_parrent(F,Y),
    female(X),
    not(is_parrent(X,Y)).

%Dependencies
is_equal_marriage(X,Y):-
    marriage(X,Y);
    marriage(Y,X).

is_equal_not_parrent(X,Y):-
    is_parrent(X,Temp),
    not(is_parrent(Y,Temp)).

%Data Marriage
marriage(stepan,olena).
marriage(oleg,oksana).
marriage(vlad,daruna).
marriage(oleksii,nastya).

%Data Parrent (Who,child)
is_parrent(oksana,igor).
is_parrent(oleksii,vasil).
is_parrent(nastya,vasil).
is_parrent(oleg,zoya).
is_parrent(oksana,zoya).
is_parrent(oleksii,valeria).

%gender
male(stepan).
male(oleg).
male(vlad).
male(oleksii).
male(igor).
male(vasil).

female(olena).
female(oksana).
female(daruna).
female(nastya).
female(zoya).
female(valeria).
