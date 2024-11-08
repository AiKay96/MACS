import BasicStore.Product;
import BasicStore.Products;
import junit.framework.TestCase;

import java.sql.SQLException;
import java.util.ArrayList;

public class ProductsTest extends TestCase {
    public void  testProducts() throws SQLException, ClassNotFoundException {
        Products pr = new Products();
        ArrayList<Product> prs = pr.getProducts();
        assertEquals(14, prs.size());
        Product product = Products.findProduct("TC");
        assertEquals("TC", product.getProductID());
        assertEquals("Classic Tee", product.getProductName());
        assertEquals(40.0, prs.get(0).getPrice());
        product.getImageFile();
    }
}