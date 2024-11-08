package BasicStore;

import javax.servlet.*;
import javax.servlet.http.*;
import java.io.IOException;

public class ProductsServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        request.getRequestDispatcher("ProductPage.jsp").forward(request, response);
    }
}
