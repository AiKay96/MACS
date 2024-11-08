import junit.framework.TestCase;
import org.apache.commons.dbcp2.BasicDataSource;
import org.junit.jupiter.api.BeforeEach;
import org.apache.commons.dbcp2.BasicDataSource;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Optional;

public class MetropolisesDBTest extends TestCase {
    private static final String DELETE_COMMAND = "DELETE FROM";
    private static final String USING_COMMAND = "USE";
    private static final String URL = "jdbc:mysql://localhost:3306/dbl";
    private static final String USERNAME = "root";
    private static final String PASSWORD = "1234";
    private static final String DATABASE_NAME = "OOP_DATABASE";
    private static final String TABLE_NAME = "metropolises";
    private static final int METROPOLIS_COLUMN = 0;
    private static final int CONTINENT_COLUMN = 1;
    private static final int POPULATION_COLUMN = 2;
    private static final int COLUMN_NUMBER = 3;
    BasicDataSource dataSource;
    MetropolisesJTable table;
    Connection connection;

    protected void setUp() throws Exception{
        super.setUp();
        table = new MetropolisesJTable(DATABASE_NAME, TABLE_NAME);
        connection = table.database.connection;
    }
    private void reNewDatabase() throws SQLException {
        Statement statement = connection.createStatement();
        statement.execute(makeBasicStatement(USING_COMMAND, DATABASE_NAME));
        statement.execute(makeBasicStatement(DELETE_COMMAND, TABLE_NAME));
        statement.close();
    }

    public void testSimplePre() throws SQLException {
        reNewDatabase();
        assertEquals(table.getRowCount(), 0);
        assertEquals(table.getColumnCount(), COLUMN_NUMBER);
        assertEquals(table.getColumnName(METROPOLIS_COLUMN), "Metropolis");
        assertEquals(table.getColumnName(CONTINENT_COLUMN), "Continent");
        assertEquals(table.getColumnName(POPULATION_COLUMN), "Population");
        assertNull(table.getColumnName(COLUMN_NUMBER));
    }

    public void testAdd() throws SQLException {
        reNewDatabase();
        table.add("a", "b", "50");
        assertEquals(table.getRowCount(), 1);
        assertEquals(table.getColumnCount(), COLUMN_NUMBER);
        assertNull(table.getValueAt(1, METROPOLIS_COLUMN));
        assertNull(table.getValueAt(0, COLUMN_NUMBER));
        assertEquals(table.getValueAt(0, METROPOLIS_COLUMN), "a");
        assertEquals(table.getValueAt(0, CONTINENT_COLUMN), "b");
        assertEquals(table.getValueAt(0, POPULATION_COLUMN), "50");
        table.add("c", "d", "20");
        assertEquals(table.getRowCount(), 2);
        assertEquals(table.getColumnCount(), COLUMN_NUMBER);
        assertNull(table.getValueAt(2, METROPOLIS_COLUMN));
        assertNull(table.getValueAt(1, COLUMN_NUMBER));
        assertEquals(table.getValueAt(1, METROPOLIS_COLUMN), "c");
        assertEquals(table.getValueAt(1, CONTINENT_COLUMN), "d");
        assertEquals(table.getValueAt(1, POPULATION_COLUMN), "20");
    }

    public void testSearch1() throws SQLException {
        reNewDatabase();
        table.add("ana", "bana", "500");
        table.add("nana", "ana", "400");
        table.add("metro", "polis", "10");
        table.search("ana", "", "", true, true);
        assertEquals(table.getRowCount(), 1);
        table.search("ana", "", "", true, false);
        assertEquals(table.getRowCount(), 2);
        table.search("", "ana", "", true, true);
        assertEquals(table.getRowCount(), 1);
        table.search("", "ana", "", true, false);
        assertEquals(table.getRowCount(), 2);
        table.search("", "", "200", true, true);
        assertEquals(table.getRowCount(), 2);
        table.search("", "", "200", false, true);
        assertEquals(table.getRowCount(), 1);
        table.search("ana", "ana", "", true, false);
        assertEquals(table.getRowCount(), 2);
        table.search("metro", "polis", "50", false, true);
        assertEquals(table.getRowCount(), 1);
        table.search("", "", "0", true, true);
        assertEquals(table.getRowCount(), 3);
    }
    public void testSearch2() throws SQLException {
        reNewDatabase();
        assertEquals(table.getRowCount(), 0);
        table.search("", "", "0", true, true);
        assertEquals(table.getRowCount(), 0);
        table.add("metropolis", "continent", "0");
        table.search("", "", "0", true, true);
        assertEquals(table.getRowCount(), 0);
        table.search("", "", "0", false, true);
        assertEquals(table.getRowCount(), 0);
        table.search("continent", "metropolis", "", true, true);
        assertEquals(table.getRowCount(), 0);
        table.search("", "","100", false, true);
        assertEquals(table.getRowCount(), 1);
    }
    public void testSearch3() throws SQLException {
        reNewDatabase();
        table.add("Mumbai","Asia","20400000");
        table.add("New York","North America","21295000");
        table.add("San Francisco","North America","5780000");
        table.add("London","Europe","8580000");
        table.add("Rome","Europe","2715000");
        table.add("Melbourne","Australia","3900000");
        table.add("San Jose","North America","7354555");
        table.add("Rostov-on-Don","Europe","1052000");
        assertEquals(table.getRowCount(), 8);
        table.search("", "", "0", true, true);
        assertEquals(table.getRowCount(), 8);
        table.search("", "A", "4000000", true, false);
        assertEquals(table.getRowCount(), 4);
        table.search("", "America", "4000000", true, false);
        assertEquals(table.getRowCount(), 3);
        table.search("e", "", "4000000", false, false);
        assertEquals(table.getRowCount(), 2);
        table.search("Tbilisi", "", "", true, true);
        assertEquals(table.getRowCount(), 0);
        table.search("", "Europe", "", true, true);
        assertEquals(table.getRowCount(), 3);
        table.search("o", "Europe", "", true, false);
        assertEquals(table.getRowCount(), 3);
        table.search("o", "Europe", "8000000", false, false);
        assertEquals(table.getRowCount(), 2);
    }

    public void testMetropolisesInfo() {
        MetropolisesInfo metropolis = new MetropolisesInfo("a", "b", "50");
        assertEquals(metropolis.getMetropolis(), "a");
        assertEquals(metropolis.getContinent(),  "b");
        assertEquals(metropolis.getPopulation(), "50");
        metropolis = new MetropolisesInfo("c", "c", "100");
        assertEquals(metropolis.getMetropolis(), metropolis.getContinent());
        assertEquals(metropolis.getPopulation(), "100");
    }
    private String makeBasicStatement(String command, String codeArgument){
        String codeLine = "";
        codeLine += command;
        codeLine += " ";
        codeLine += codeArgument;
        codeLine += ";";
        return codeLine;
    }
}