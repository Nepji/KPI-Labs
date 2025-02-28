use `library db 3sem`;
REPAIR TABLE tables_priv;
-- Завдання 1 -------------------------------
CREATE USER 'TestUser1`@`localhost' IDENTIFIED BY '123456789';
CREATE USER 'TestUser2`@`localhost' IDENTIFIED BY '987654321';

GRANT all privileges on `author` to TestUser1;
GRANT SELECT on `author` to TestUser2;

SELECT user();

drop user 'TestUser2`@`localhost';
-- Завдання 2 -------------------------------

START TRANSACTION;
	insert into author(FirstName,LastName) values ('TEST','TEST');
rollback;

START TRANSACTION;
	insert into author(FirstName,LastName) values ('SMT','NONE');
    savepoint save;
    insert into author(FirstName,LastName) values ('NONE','SMT');
    ROLLBACK TO SAVEPOINT save;
commit;

START TRANSACTION;
	select * from author lock in share mode;
	insert into author(FirstName,LastName) values ('NONE','NONE');
    select count(*) from author;
rollback;
UNLOCK TABLES;

-- ------------------------------------------

-- Завдання 3 -------------------------------
SET TRANSACTION ISOLATION LEVEL READ UNCOMMITTED;

START TRANSACTION;
	update author set FirstName = 'NewNone' where LastName = 'NONE';
    select * from author;
rollback;

-- ------------------------------------------