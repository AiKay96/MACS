<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 20:14
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
    <head>
        <title>Create Account</title>
    </head>
    <body>
    <h1> The Name <%=request.getParameter("username")%> is Already In Use </h1>
    <p> Please enter another name and password. </p>
    <form action = "createAccount" method = "POST">
        User Name: <input id = "username" type = "text" name = "username"/><br>
        Password: <input id = "password" type = "text" name= "password"/>
        <button type="submit" > Login </button>
    </form>
    </body>
</html>
