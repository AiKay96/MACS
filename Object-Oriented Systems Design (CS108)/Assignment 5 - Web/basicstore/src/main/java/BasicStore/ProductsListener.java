package BasicStore;

import javax.servlet.ServletContext;
import javax.servlet.ServletContextEvent;
import javax.servlet.ServletContextListener;
import javax.servlet.annotation.WebListener;
import java.sql.SQLException;

@WebListener
public class ProductsListener implements ServletContextListener {
    private Products products;
    public ProductsListener() throws SQLException {
        products = new Products();
    }
    @Override
    public void contextInitialized(ServletContextEvent servletContextEvent) {
        ServletContext sc = servletContextEvent.getServletContext();
        sc.setAttribute("Products", products);
    }

    @Override
    public void contextDestroyed(ServletContextEvent servletContextEvent) {

    }

}

