package BasicStore;

import org.apache.commons.dbcp2.BasicDataSource;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;

public class Products {

    private static final String URL = "jdbc:mysql://localhost:3306/AMWYD";
    private static final String USERNAME = "root";
    private static final String PASSWORD = "1234";
    public static final String DATABASE_NAME = "AMWYD";
    private static Connection connection;
    public Products() throws SQLException {
        BasicDataSource dataSource = new BasicDataSource();
        dataSource.setUrl(URL);
        dataSource.setUsername(USERNAME);
        dataSource.setPassword(PASSWORD);
        connection = dataSource.getConnection();
    }

    public ArrayList<Product> getProducts() throws SQLException {
        Statement statement = connection.createStatement();
        statement.execute("USE " + DATABASE_NAME + ";");
        ResultSet resultSet = statement.executeQuery("SELECT * FROM PRODUCTS;");

        ArrayList<Product> results = new ArrayList<>();

        while (resultSet.next())
            results.add(new Product(resultSet.getString(1), resultSet.getString(2),
                    resultSet.getString(3), resultSet.getDouble(4)));

        return results;
    }

    public static Product findProduct(String productID) throws SQLException {
        Product ans = null;
        StringBuilder sqlScript =new StringBuilder("Select * from products where productid = '" + productID + "';");
        Statement statement = connection.createStatement();
        ResultSet resultSet = statement.executeQuery(sqlScript.toString());
        if(resultSet.next()){
            ans = new Product(resultSet.getString(1),resultSet.getString(2),
                    resultSet.getString(3),resultSet.getDouble(4));
        }
        return ans;
    }
}
