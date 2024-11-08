<%--
  Created by IntelliJ IDEA.
  User: AiKay96
  Date: 06/08/23
  Time: 19:22
  To change this template use File | Settings | File Templates.
--%>
<%@ page import="BasicStore.*" %>
<%@ page import="java.util.HashMap" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" pageEncoding="UTF-8"%>
<html>
    <head>
        <title>Shopping Cart</title>
    </head>
    <body>
    <h1>Shoping Cart </h1>
    <%
        ShoppingCart cart = (ShoppingCart)request.getSession().getAttribute("ShoppingCart");
        HashMap<String, Integer> mp = cart.getAllProducts();
        Products pr = new Products();
        Double sum = 0.0;
    %>
    <form action="shopping" method="POST">
        <ul>
            <%
                for(String productID : mp.keySet()){
                    Product product = pr.findProduct(productID);
                    int num = mp.get(productID);
                    sum += product.getPrice()*num;
                    out.println(
                            "<li> <p> <input type = \"text\" value=" + num + " name=" +productID+ " />"+
                                    " " + product.getProductName() + " " + product.getPrice()+ "</p> </li>"
                    );
                }%>
        </ul>
        Total: <%=Math.round(sum * 100)/100.0%> <input type="submit" value="UpdateCart">
    </form>
    <a href="index.jsp"> Continue Shopping</a>
    </body>
</html>