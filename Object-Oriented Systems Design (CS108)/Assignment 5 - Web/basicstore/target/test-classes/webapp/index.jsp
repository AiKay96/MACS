<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 19:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="BasicStore.*" %>
<%@ page import="java.util.ArrayList" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
    <head>
        <title>Student Store</title>
    </head>
    <body>
    <h1> Student Store </h1>
    <p> Items available: </p>
    <ul>
        <%    Products products = (Products) request.getServletContext().getAttribute("Products");%>
        <%    ArrayList<Product> all = products.getProducts();%>
        <%    for(int i=0;i<all.size();i++){%>
        <li><a href="product?productID=<%= all.get(i).getProductID() %>"><%= all.get(i).getProductName() %></a></li>
        <%    }%>
    </ul>
    </body>
</html>
