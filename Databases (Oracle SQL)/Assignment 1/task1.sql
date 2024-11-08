/*
დაწერეთ სელექთი, რომლიც დაბეჭდავს: 
            თანამშრომლის სახელსა და გვარს გადაბმული  -> ' - ' <- სიმბოლოებით სვეტს დაარქვით ზუსტად ასე: F and L, 
    დეპარტამენტის სახელს(არსებობის შემთხვევაში თუარადა X-ს), 
    მენეჯერის სახელს
    ხელფასს $12,000.00 ფორმატით
    მენეჯერის მენეჯერის სახელს 
    მენეჯერის მენეჯერის ხელფასს
  ეს ინფორმაცია  დაბეჭეთ მხოლოდ ისეთი თანამშრომლებზე, რომლეთა მენეჯერის მენეჯერის სახელში გვხვდება a სიმბოლო ( სიმბოლოს ზომას არ აქვს მნიშვნელობა)
               და მენეჯერის მენეჯერის ხელფასი 17-ის ჯერადია.
*/

SELECT e.first_name || q'[' - ']' || e.last_name AS "F and L",
       nvl2(d.department_name, d.department_name, 'X') AS "DEPATMENT_NAME",
       m.first_name,
       to_char(e.salary, '$999,999,999.00'),
       mm.first_name,
       mm.salary
FROM employees e
JOIN departments d ON (e.department_id = d.department_id)
JOIN employees m ON (e.manager_id = m.employee_id)
JOIN employees mm ON (m.manager_id = mm.employee_id)
WHERE mm.first_name like '%a%'
  AND mod(mm.salary, 17) = 0;