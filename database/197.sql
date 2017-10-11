select a.Id from Weather as a inner join Weather as b on datediff(a.Date, b.Date) = 1 and a.Temperature > b.Temperature
