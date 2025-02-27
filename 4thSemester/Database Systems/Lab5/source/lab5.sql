use lab2;

select * from library;
select * from genres;
select * from author;

-- ---------------------------------------
select B_Name, B_Count,
Case
When B_Count = 0 then 'Out of stocks'
when B_Count > 0 and B_Count < 5 then 'product is running out'
when B_Count > 5 then 'all good'
else 'Error'
end as B_Status
from library;

 select B_Name, B_Count,
Case B_Count
When 0 then 'Out of stocks'
when 1 and B_Count < 5 then 'product is running out'
when 2 then 'all good'
else 'Error'
end as B_Status
from library;
-- ---------------------------------------
select B_Name, B_Cost, if(B_Cost<500,"<500",">500") as Comp from library;
-- ---------------------------------------

select B_Name, B_Cost,
case
when B_Count = 0 then 'Out of stocks'
when B_Count > 0 and B_Count < 5 then 'product is running out'
when B_Count > 5 then 'all good'
else 'Error'
end as B_Status
from library
order by B_Name;

select B_Name, B_Cost,
case
when B_Count = 0 then 'Out of stocks'
when B_Count > 0 and B_Count < 5 then 'product is running out'
when B_Count > 5 then 'all good'
else 'Error'
end as B_Status
from library
where B_Cost in (500,700);

select B_Name, B_Cost, sum(B_Count),
case
when sum(B_Count) = 0 then 'Out of stocks'
when sum(B_Count) > 0 and sum(B_Count) < 5 then 'product is running out'
when sum(B_Count) > 5 then 'all good'
else 'Error'
end as B_Status
from library
group by B_Name, B_Cost
having sum(B_Count)>7;

-- ---------------------------------------
Delete from library where if(B_Cost<500,1,0);

update library set B_Pledge =
case
when B_Cost > 500 then B_Pledge * 2
when B_Cost < 500 and B_Cost > 0 then B_Pledge / 2
else B_Pledge end;
-- ---------------------------------------
SELECT COALESCE(NULL,'SMT');
Select B_id,B_Name, B_Count, coalesce(B_Pledge, 1000) from library;
-- ---------------------------------------
select * from genres
union
select * from author;
