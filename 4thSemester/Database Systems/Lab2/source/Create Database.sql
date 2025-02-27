create database lab2;
use lab2;

create table Genres
(
G_id int not null auto_increment,
Genre varchar(35) unique,

primary key(G_id)
) engine innodb;

create table author
(
A_id int not null auto_increment,
A_FullName varchar(255),

primary key (A_id)
) engine = innodb;

create table library
(
B_id int not null auto_increment,
B_Name varchar(35),
B_Count int,
B_Cost int not null,
B_Pledge int not null,

Genre int,
B_Author int,

foreign key (Genre) 
	references Genres(G_id),
foreign key (B_Author)
	references author(A_id),
    
primary key (B_id)
) engine = innodb;

create table Debtor_Info
(
D_id int auto_increment,
D_PassportId int unique,
D_FIO varchar(35),
D_address varchar(255),
D_mobilenumber long,

primary key (D_id)
)engine = innodb;

create table Loans
(
id int auto_increment,
rentdate_start date not null,
rentdate_end date not null,
loan_allowance int not null, 
rentDebt int,
rentBook int not null,
forfeit int not null,
Sale int,


foreign key (rentBook) 
	references library(B_id),

primary key (id)
) engine = innodb;


create table Debtor_list
(
D_id int auto_increment,
D_debtorId int not null,
D_LoanId int unique,
foreign key (D_debtorId) 
	references Debtor_Info(D_id),
foreign key (D_LoanId) 
	references Loans(id),

primary key (D_id)
) engine = innodb;


 /*   
select * from Debtor_info;
select * from Debtor_List;
select * from Loans;
select * from library;
select * from Author;
select * from Genres;
*/
 /* 
drop table Debtor, library,Author,Genres;
drop database lab2;
*/
