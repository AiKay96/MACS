<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 19:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
    <head>
        <title>WELCOME</title>
    </head>
    <body>
    <h1> Welcome to Homework 5 </h1>
    <p> Please log in. </p>
    <form action = "LogIn" method = "POST">
        User Name: <input id = "username" type = "text" name = "username"/><br>
        Password: <input id = "password" type = "text" name= "password"/>
        <button type="submit" > Login </button>
    </form>
    <p> <a href = "createAccount"> Create New Account </a> </p>
    </body>
</html>
