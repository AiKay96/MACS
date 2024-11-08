<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 19:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="BasicStore.*" %>
<%@ page contentType="text/html;charset=UTF-8" language="java"%>
<html>
  <head>
    <% Products products = (Products) request.getServletContext().getAttribute("Products"); %>
    <%  Product product = products.findProduct((String)request.getParameter("productID"));%>
    <title><%= product.getProductName() %></title>
  </head>
  <body>
    <h1> <%= product.getProductName() %> </h1>
    <img src = "store-images/<%= product.getImageFile() %>" alt = "not found" width="200" height="200"><br>
    <form action="shopping" method="POST">
      <input name="productID" type="hidden" value="<%=product.getProductID()%>"/>
      <%=product.getPrice()%> <input type="submit" value="Add to Cart">
    </form>
  </body>
</html>
