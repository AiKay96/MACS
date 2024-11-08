package UserLogin;

import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class LogInServlet extends HttpServlet {
    public LogInServlet() {
        super();
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        RequestDispatcher requestDispatcher = request.getRequestDispatcher("/index.jsp");
        requestDispatcher.forward(request,response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        AccountManager accountManager = (AccountManager) request.getServletContext().getAttribute("Account Manager");
        if(accountManager.matchPassword(request.getParameter("username"), request.getParameter("password"))){
            RequestDispatcher requestDispatcher = request.getRequestDispatcher("UserWelcomePage.jsp");
            requestDispatcher.forward(request,response);
        }else{
            RequestDispatcher requestDispatcher = request.getRequestDispatcher("TryAgainPage.jsp");
            requestDispatcher.forward(request,response);
        }
    }
}
