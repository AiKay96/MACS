import org.apache.commons.dbcp2.BasicDataSource;

import javax.swing.plaf.nimbus.State;
import java.sql.*;
import java.util.ArrayList;

public class MetropolisesDataBase {
    private static final String URL = "jdbc:mysql://localhost:3306/dbl";
    private static final String USERNAME = "root";
    private static final String PASSWORD = "1234";
    private static final String USING_COMMAND = "USE";
    private static final String WHERE_COMMAND = "WHERE";
    private static final String EQUAL_COMMAND = "=";
    private static final String LIKE_COMMAND = "LIKE";
    private static final String AND_COMMAND = "AND";
    private static final String INSERT_COMMAND = "INSERT INTO";
    private static final String SELECT_COMMAND = "SELECT * FROM";
    private String databaseName;
    private String tableName;
    Connection connection;
    public MetropolisesDataBase(String databaseName, String tableName)
            throws SQLException, ClassNotFoundException {
        this.databaseName = databaseName;
        this.tableName = tableName;

        setUpConnection();
    }
    /**
     * Creates and sets up connection.
     * @throws SQLException
     */
    private void setUpConnection() throws SQLException {
        BasicDataSource dataSource = new BasicDataSource();
        dataSource.setUrl(URL);
        dataSource.setUsername(USERNAME);
        dataSource.setPassword(PASSWORD);
        connection = dataSource.getConnection();
    }

    /**
     * @param metropolis
     * @param continent
     * @param population
     * Adds new metropolis to the SQLtable.
     * @throws SQLException
     */
    public void addMetropolis(String metropolis, String continent, String population) throws SQLException {
        Statement state = connection.createStatement();
        state.execute(makeBasicStatement(USING_COMMAND,databaseName));
        state.close();
        PreparedStatement statement = connection.prepareStatement
                (makeBasicStatement(INSERT_COMMAND, tableName + " " + "VALUES (?, ?, ?);"));
        statement.setString(1, metropolis);
        statement.setString(2, continent);
        statement.setString(3, population);
        statement.execute();
        statement.close();
    }
    /**
     * @param metropolis
     * @param continent
     * @param population
     * @param wantLarger
     * @param wantExact
     * Searches metropolises for certain parameters.
     * @throws SQLException
     */
    public ArrayList<MetropolisesInfo> searchMetropolises(String metropolis, String continent, String population,
                                   boolean wantLarger, boolean wantExact) throws SQLException {
        boolean usedWhereCommand = false;
        ArrayList<String> Args = new ArrayList<>();
        Args.add(SELECT_COMMAND);
        Args.add(tableName);
        if(!metropolis.equals("")){
            Args.add(WHERE_COMMAND);
            Args.add("metropolis");
            if(wantExact) {
                Args.add(EQUAL_COMMAND);
                Args.add("'" + metropolis + "'");
            }else {
                Args.add(LIKE_COMMAND);
                Args.add("'%" + metropolis + "%'");
            }
            usedWhereCommand = true;
        }
        if(!continent.equals("")){
            if(!usedWhereCommand)
                Args.add(WHERE_COMMAND);
            else
                Args.add(AND_COMMAND);
            Args.add("continent");
            if(wantExact) {
                Args.add(EQUAL_COMMAND);
                Args.add("'" + continent + "'");
            }else {
                Args.add(LIKE_COMMAND);
                Args.add("'%" + continent + "%'");
            }
            usedWhereCommand = true;
        }
        if(!population.equals("")){
            if(!usedWhereCommand)
                Args.add(WHERE_COMMAND);
            else
                Args.add(AND_COMMAND);
            Args.add("population");
            if(wantLarger)
                Args.add(">");
            else
                Args.add("<");
            Args.add(population);
        }

        Statement statement = connection.createStatement();
        statement.execute(makeBasicStatement(USING_COMMAND,databaseName));
        ResultSet resultSet = statement.executeQuery(makeSelectStatement(Args));

        ArrayList<MetropolisesInfo> results = new ArrayList<>();

        while (resultSet.next())
            results.add(new MetropolisesInfo(resultSet.getString(1), resultSet.getString(2),
                    resultSet.getString(3)));

        return results;
    }
    /**
     * @param args
     * Generates 'select' SQL statement by appending arguments and ';' symbol.
     */
    private String makeSelectStatement(ArrayList<String> args) {
        StringBuilder codeLine = new StringBuilder();
        codeLine.append(args.get(0));
        for(int i = 1; i < args.size(); i++){
            codeLine.append(" ");
            codeLine.append(args.get(i));
        }
        codeLine.append(";");
        return codeLine.toString();
    }

    /**
     * @param command
     * @param codeArgument
     * Generates simple SQL statement by appending arguments and ';' symbol.
     */
    private String makeBasicStatement(String command, String codeArgument){
        String codeLine = "";
        codeLine += command;
        codeLine += " ";
        codeLine += codeArgument;
        codeLine += ";";
        return codeLine;
    }
}
