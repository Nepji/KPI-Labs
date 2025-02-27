create database lab1;
use lab1;

create table library(
id int primary key auto_increment not null,
username varchar(35),
Bookname varchar(35),
return_data date, 
rent_cost float
);

insert into library(username, bookname, return_data, rent_cost)
	values 	('NoPitches', 'WhatIsLove','2004.04.15',5400),
			('Akira228','AnimeOnline', '3008.11.11',1347);

load data local infile 'D:\lab1lib.txt' 
	into table library
	FIELDS terminated by ','
	optionally enclosed by '"'
	lines terminated by '\r\n'
	ignore 1 lines
	(id,username, bookname, return_data, rent_cost);


Update library
	set id = 1
    where id = 1;

Delete from library
	where id = 8;
    
truncate library;
        
Alter table library drop column rent_cost;

show tables;
select * from library;

drop table library;
drop database lab1;