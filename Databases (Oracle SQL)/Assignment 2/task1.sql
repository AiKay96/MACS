/*
დაწერეთ სლექთი, რომელიც დეპარტამენტების შესახებ დაბეჭდავს შემდეგ ინფორმაციას:
- department_name დეპარტამენტის სახელი
- emp_cnt რამდენი თანამშრომელი მუშაობს ამ დეპარტამენტში, თუ არავინ მუშაობს დაბეჭდეთ 'N/A'
- job_cnt რამდენი განსხვავებული პოზიციაა ამ დეპარტამენტზე, თუ არცერთი არაა დაბეჭდეთ 'N/A'
- sum_sal ჯამური ხელფასი ამ დეპარტამენტზე, NULL ის შემთხვევაში  დაბეჭდეთ 'N/A'
- sum_min_max მინიმლაური და მაქსიმალური ხელფასების ჯამი ამ დეპარტამენტზე, NULL ის შემთხვევაში  დაბეჭდეთ 'N/A'
- phone_numbers დეპარტამენტში არსებული თანამშრომლების ტელეფონის ნომრები აკინძული ", " სიმბოლოთი დალაგებული ხელფასის ზრდადობით, თუ X დეპარტამენტში 2 თანამშრომელია, ერთის ტელეფონის ნომერია 123 ხოლო მერეოსი 456 უნდა დაიბეჭდოს X დეპარტამენტისთვის "123, 456".
გამორიცხეთ ისეთი დეპარტამენტები, რომლების დეპარტამენტის სახელი 2 ან 2-ზე მეტ სიტყვიანია, თუ დეპარტამენტის სახელია "A" უნდა დაბეჭდოთ, მაგრამ თუ დეპარტამენტის სახელია "A B" მაშინ არ უნდა დაბეჭდოთ.
ასევე გამორიცხეთ დეპარტამენტბი, რომლებიც არ მდებარეობენ ისეთ ქვეყანაში, რომლისთვისაც COUNTRY_ID არაა COUNTRY_NAME-ის დასაწყისი, რეგისტრს მნიშვნელობა არ აქვს.
მონაცემები დაალაგეთ ქვეყენბის  აიდიების ზრდადობითა და ქვეყნის სახელების კლებადობით.
*/

SELECT d.department_name,
       CASE
           WHEN (count(e.employee_id) = 0) THEN 'N/A'
           ELSE to_char(count(e.employee_id))
       END AS emp_cnt,
       CASE WHEN(count(DISTINCT job_id) = 0) THEN 'N/A'
           ELSE to_char(count(DISTINCT job_id))
       END AS job_cnt,
       NVL2(sum(e.salary), to_char(sum(e.salary)), 'N/A') AS sum_sal,
       NVL2(min(salary) + max(salary), to_char(min(salary) + max(salary)), 'N/A') AS sum_min_max,
       LISTAGG(e.phone_number, ', ') WITHIN GROUP (
                                                   ORDER BY e.phone_number ASC) AS phone_numbers
FROM departments d
LEFT JOIN employees e ON (d.department_id = e.department_id)
JOIN locations l ON (d.location_id = l.location_id)
JOIN countries c ON (l.country_id = c.country_id)
WHERE d.department_name not like '% %'
  AND upper(c.country_id) = upper(substr(c.country_name, 1, length(c.country_id)))
GROUP BY d.department_name,
         c.country_id,
         c.country_name
ORDER BY c.country_id ASC,
         c.country_name DESC;