select
    Request_at as Day,
    round(sum(case Status when 'completed' then 0 else 1 end) / sum(1), 2) as "Cancellation Rate"
from Trips as a inner join Users as b on a.Client_Id = b.Users_id and b.Banned = 'No'
where a.Request_at >= '2013-10-01' and a.Request_at <= '2013-10-03'
group by 1;
    
