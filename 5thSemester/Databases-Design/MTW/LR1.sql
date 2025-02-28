
create view custom_worker  as select WorkerID, FirstName, SecondName from worker;
select * from custom_worker;
drop view custom_worker;


-- /////////////////////////////////////////////////////////////////////

UPDATE custom_worker set FirstName = "Володька" where WorkerID = 1;
select * from custom_worker;
select * from worker;

-- create materialized view custom_worker  as select WorkerID, FirstName, SecondName from worker;

-- /////////////////////////////////////////////////////////////////////

CREATE VIEW custom_contact AS
SELECT cFirst.FirstName, cSecond.ContactType, cSecond.Value
FROM visitor as cFirst
JOIN visitorcontact as cSecond ON cFirst.VisitorID = cSecond.VisitorID;

select * from custom_contact;
drop view custom_contact;

-- /////////////////////////////////////////////////////////////////////
