/*
დაწერეთ სლექთი, რომელიც პოზიციების შესახებ დაბეჭდავს შემდეგ ინფორმაციას:
- job_id პოზიციის აიდი
- name პოზიციის სახელი
- emp_cnt  ამ პოზიციაზე მომუშავე კენტ EMPLOYEE_ID-ის მქონე თანამშრომლების რაოდენობა, არარსებობის შემთხვევაში 'N/A'
- avg_sal ამ პოზიციაზე მომუშავე ლუწ EMPLOYEE_ID-ის ქმონე თანამშრომლების საშუალო ხელფასი, არარსებობის შემთხვევაში 'N/A'
- mx_cnt ამ პოზიციაზე მაქსიმალურ ხელფასის მქონე თანამშრომლების რაოდენობა, არარსებობის შემთხვევაში 'N/A'
გამორიცხეთ ისეთი პოზიციები, რომლების აიდიც 4 სიმბოლოზე ნაკლებია.
გამორიცხეთ პოზიციები, რომლებშიც MAX_SALARY-ისა და MIN_SALARY-ის სხვაობა მაქსიმალურია.
მონაცემები დაალაგეთ, პოზიციის აიდით, ისე რომ ჯერ ჩანდეს IT პოზიციები, ანუ პოზიციები რომელთა ID ში IT ურევია, შემდეგ ყველა სხვა დანარჩენი ალფაბეტიკურად.
*/

SELECT j.job_id,
       j.job_title AS name,
       CASE
           WHEN (COUNT(CASE
                           WHEN (MOD(e.employee_id, 2) = 1) THEN 1
                       END) = 0) THEN 'N/A'
           ELSE TO_CHAR(COUNT(CASE
                                  WHEN (MOD(e.employee_id, 2) = 1) THEN 1
                              END))
       END AS emp_cnt,
       NVL2(AVG(CASE
                    WHEN (MOD(e.employee_id, 2) = 0) THEN e.salary
                END), TO_CHAR(AVG(CASE
                                      WHEN (MOD(e.employee_id, 2) = 0) THEN e.salary
                                  END)), 'N/A') AS avg_sal,
       CASE
           WHEN (COUNT(CASE
                           WHEN (e.salary =
                                   (SELECT MAX(emp.salary)
                                    FROM employees emp
                                    WHERE j.job_id = emp.job_id)) THEN 1
                       END) = 0)THEN 'N/A'
           ELSE TO_CHAR(COUNT(CASE
                                  WHEN (e.salary =
                                          (SELECT MAX(emp.salary)
                                           FROM employees emp
                                           WHERE j.job_id = emp.job_id)) THEN 1
                              END))
       END AS mx_cnt
FROM jobs j
LEFT JOIN employees e ON j.job_id = e.job_id
WHERE LENGTH(j.job_id) >= 4
  AND j.max_salary - j.min_salary !=
    (SELECT MAX(jb.max_salary - jb.min_salary)
     FROM jobs jb)
GROUP BY j.job_id,
         j.job_title
ORDER BY CASE
             WHEN (j.job_id like '%IT%') THEN 0
             ELSE 1
         END,
         j.job_id;