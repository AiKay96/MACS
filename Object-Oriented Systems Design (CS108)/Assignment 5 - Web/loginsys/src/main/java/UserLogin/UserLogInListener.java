package UserLogin;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;

@WebListener
public class UserLogInListener implements ServletContextListener {
    private AccountManager accountManager;

    public UserLogInListener(){
        accountManager = new AccountManager();
    }
    @Override
    public void contextInitialized(ServletContextEvent servletContextEvent) {
        ServletContext sc = servletContextEvent.getServletContext();
        sc.setAttribute("Account Manager", accountManager);
    }

    @Override
    public void contextDestroyed(ServletContextEvent servletContextEvent) {

    }
}
