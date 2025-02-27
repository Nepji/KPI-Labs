use lab2;

select * from library;
-- 1.
select B_id,B_Count from library;

select * from library where B_Count>10 and B_Cost<500;
select * from library where Genre=1 or B_Pledge=2500;
select * from library where not B_Author=7;

select * from library where B_Cost in (500,750);
select * from library where B_Count between 5 and 10;
select * from library where B_Pledge like '_500';
select * from loans where Sale is null;

-- 2
select * from library;
select * from genres;
select * from library order by B_Cost;
select * from genres order by Genre;

-- 3
select * from library;
select * from genres;
select library.B_Name, genres.Genre from library join genres on library.B_id = genres.G_id;

select * from author right outer join genres on author.A_id = genres.G_id;
select * from genres left outer join author on author.A_id = genres.G_id;
select * from author inner  join genres on author.A_id = genres.G_id;

-- 4
select distinct B_Author from library;
select * from library where B_Pledge>1000 limit 2;
