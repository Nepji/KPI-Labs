--
select * from author;
SET TRANSACTION ISOLATION LEVEL SERIALIZABLE;
SET AUTOCOMMIT = 0;
--


START TRANSACTION;
	insert into author(FirstName,LastName) values ('Volodya','Black');
Commit;

START TRANSACTION;
	insert into author(FirstName,LastName) values ('NONE','NONE');
rollback;

START TRANSACTION;
	insert into author(FirstName,LastName) values ('SMT','NONE');
    savepoint save;
    insert into author(FirstName,LastName) values ('NONE','SMT');
    ROLLBACK TO SAVEPOINT save;
commit;

--

START TRANSACTION;
	-- select * from author lock in share mode;
	select * from author for UPDATE;
	insert into author(FirstName,LastName) values ('NONE','NONE');
    select count(*) from author;
rollback;

    select * from author lock in share mode;