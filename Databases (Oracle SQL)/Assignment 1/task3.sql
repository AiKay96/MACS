/*
jobs ცხრილში მოცემულია თანამშრომლების პოზიციები.
    მაგ: IT_PROG,PU_CLERK,MK_MAN, MK_REP  და სხვა.
 გამოიტანეთ ინფორმაცია:
• პოზიციის პრექფიქსი (პრექფიქსი არის JOIB_ID ის მნიშვნელობა მარცხნიდან ქვედა ხაზამდე, 
  გაითვალისწინეთ შეიძლება ქვედა ხაზი არ იყოს მე-3 პოზიციაზე) - pref 
• ამ პრეფიქსით დაწყებულ პოზიციებზე თანამშრომლების რაოდენობა - count
• თუ რომელიმე პრეფიქსი მოიცავს ისეთ პოზიციას, რომელზეც არაა არცერთი თანამშრომელი დაიბეჭდოს N თუარადა Y - yn
• ამ პრეფიქსზე თანამშრომელბის საშუალო ხელფასი - avg_salary
• ამ პრეფიქსზე 2002 წელს აყვანილი თანამშრომელთა რაოდენობა - cnt_2002
ინფორმაცია დაალაგეთ ისე რომ, ჯერ დაიბეჭდოს IT  პრეფიქსის მქონე პოზიციის ინფორმაცია, შემდეგ MK პრეფიქსის მქონეს ინფორმაცია და 
           ყველა სხვა დანარჩენი საშუალო ხელფასის კლებადობით;
*/

SELECT substr(job_id, 1, (instr(job_id, '_') - 1)) AS "PREF",
       count(employee_id) AS "COUNT",
       CASE
           WHEN (count(employee_id) = 0) THEN 'N'
           ELSE 'Y'
       END AS "YN",
       avg(salary) AS "AVG_SALARY",
       sum(CASE when(extract(YEAR
                             FROM hire_date) = 2002) THEN 1
               ELSE 0
           END) AS "CNT_2002"
FROM employees
GROUP BY substr(job_id, 1, (instr(job_id, '_') - 1))
ORDER BY CASE
             WHEN ("PREF" = 'IT') THEN 1
             WHEN ("PREF" = 'MK') THEN 2
             ELSE 3
         END,
         avg(salary) DESC;