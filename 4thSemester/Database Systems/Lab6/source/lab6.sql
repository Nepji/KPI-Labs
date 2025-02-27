use lab2;

select * from library;
select * from genres;
select * from author;

-- Проекція -------------------------------------------
select B_id,B_Name,Genre from library;
-- Вибірка -------------------------------------------
select *from library where B_count >5 or B_Cost <500;
-- Об'єданння -------------------------------------------
select * from genres
union
select * from author;
-- Віднімання не має в mySQL (not in) -------------------------------------------
-- З'єднання сполучення  -------------------------------------------
select author.A_FullName, library.B_Name from author,library where author.A_id = library.B_Author;
select library.B_Name,author.A_FullName from library join author on library.B_Author = author.A_id;
-- Перетину не має inner join\in -------------------------------------------
-- Розподіл\ділення -------------------------------------------
select Genre from genres where exists (select 1 from library where library.Genre=genres.G_id and library.B_Count>9);
select Genre from genres where not exists (select 1 from library where library.Genre=genres.G_id and library.B_Count>9);


