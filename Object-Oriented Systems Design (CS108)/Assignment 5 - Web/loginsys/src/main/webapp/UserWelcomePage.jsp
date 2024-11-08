<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 20:06
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
  <head>
      <title> Welcome <%= request.getParameter("username")%> </title>
  </head>
  <body>
      <h1> Welcome <%= request.getParameter("username")%> </h1>
  </body>
</html>
