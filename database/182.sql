select Email from Person group by 1 having sum(1) > 1;
