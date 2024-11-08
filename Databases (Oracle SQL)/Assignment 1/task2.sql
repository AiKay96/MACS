/*
დაასელექთეთ ყველა ის თანამშრომელი რომლებიც, აკმაყოფილებენ შემდეგ პირობებს:
  -  მუშაობენ 50-ე დეპარტამენტში (employees.department_id) ან მიმდინარე პოზიციაზე მათი აყვანიდან გასულია მინიმუმ 5 წელი;
  -  ტელეფონის ნომერი იწყება '515' ით;
  -  არ მუშაობენ არც 'IT_PROG' და არც 'PU_CLERK' პოზიციაზე.;
  -  მათი ხელფაი არის 5000 დან 10000 მდე;
  -  ჰყავთ მენეჯერი;
დაბეჭდეთ ველები:
  - თანამშრომლის სახელი და გვარი გადაბმული შუაში ერთი "სფეისით". ველს დაარქვით full_name;
  - თანამშრომლის ხელფასი ფორმატით $XXX,XXX,XXX.XX (ზედმეტი სფეისები არ დაბეჭდოთ);
  - mail-ის '@'-მდე მოჭრილი მნიშვნელობა. თუ mail ცარიელია ან არ შეიცავს '@'_ს, დაბეჭდეთ 'INVALID MAIL';
  - მიმდინარე წელს აღებული ჯამური ხელფასი(წელს X თვე თუ არის გასული, salary * X);
  - საკომისიო. მისი არარსებობის შემთხვევაში დაბეჭდეთ 'No Com'.
მონაცემები დაალაგეთ:
  - ხელფასის კლებადობით;
  - მიმდინარე პოზიციაზე აყვანის თარიღის ზრდადობით;
*/

SELECT first_name || ' ' || last_name AS "FULL_NAME",
       trim(to_char(salary, '$999,999,999.00')) AS "MONTH_SALARY",
       CASE
           WHEN (email IS NULL
                 OR email not like '%@%') THEN 'INVALID MAIL'
           ELSE substr(email, 1, instr(email, '@') - 1)
       END AS "EMAIL",
       salary * (extract(MONTH
                         FROM sysdate) - 1) AS "SUM_SALARY",
       nvl2(commission_pct, to_char(commission_pct), 'No Com') AS "COMMISSION"
FROM employees
WHERE (department_id = 50
       OR months_between(sysdate, hire_date)/12 >= 5)
  AND phone_number like '515%'
  AND job_id != 'IT_PROG'
  AND job_id != 'PU_CLERK'
  AND salary BETWEEN 5000 AND 10000
  AND manager_id IS NOT NULL
ORDER BY salary DESC,
         hire_date ASC;