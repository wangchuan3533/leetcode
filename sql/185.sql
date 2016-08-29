select b.Name as Department, a.Name as Employee, a.Salary as Salary from Employee as a inner join Department as b on a.DepartmentId = b.Id
where (select count(distinct Salary) from Employee as c where a.DepartmentId = c.DepartmentId and a.Salary <= c.Salary) <= 3
order by 1, 3 desc;

