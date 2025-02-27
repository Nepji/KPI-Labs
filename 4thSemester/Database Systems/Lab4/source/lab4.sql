use lab2;

-- --------------------------------------------------------------------------------
select B_Author, max(B_Count) as Most_books_left from library group by B_Author;
select B_Author, min(B_Count) as Most_books_left from library group by B_Author;
select B_Author, avg(B_Count) as Most_books_left from library group by B_Author;
select B_Author, Count(B_Count) as Most_books_left from library group by B_Author;

select max(B_Count) as Most_books_left from library ;
select min(B_Count) as Min_books_left from library ;
select avg(B_Count) as AVG_books_left from library ;
select Count(B_Count) as Count_books from library ;

-- --------------------------------------------------------------------------------
select B_Author, max(B_Count) as Most_books_left from library 
group by B_Author
having max(B_Count) > 7;

select B_Author, Count(B_Count) as books_Count from library 
group by B_Author
having Count(B_Count) < 3;
-- --------------------------------------------------------------------------------