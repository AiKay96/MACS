package BasicStore;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.Enumeration;

public class ShoppingCartServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        ShoppingCart shoppingCart = (ShoppingCart) request.getSession().getAttribute("ShoppingCart");
        if (shoppingCart == null) {
            shoppingCart = new ShoppingCart();
            //newUser
            request.getSession().setAttribute("ShoppingCart", shoppingCart);
        }
        request.getRequestDispatcher("ShoppingCartPage.jsp").forward(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        ShoppingCart shoppingCart = (ShoppingCart) request.getSession().getAttribute("ShoppingCart");
        if (shoppingCart == null)
            shoppingCart = new ShoppingCart();
        String productID = request.getParameter("productID");
        if (productID != null) {
            shoppingCart.addProduct(productID);
        } else {
            Enumeration<String> productIDs = request.getParameterNames();
            while(productIDs.hasMoreElements()){
                productID = productIDs.nextElement();
                int num = Integer.parseInt(request.getParameter(productID));
                shoppingCart.changeNum(productID, num);
            }
        }
        request.getSession().setAttribute("ShoppingCart", shoppingCart);
        request.getRequestDispatcher("ShoppingCartPage.jsp").forward(request, response);
    }
}
