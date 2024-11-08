import javax.swing.table.AbstractTableModel;
import java.sql.SQLException;
import java.util.ArrayList;

public class MetropolisesJTable extends AbstractTableModel {
    private static final int METROPOLIS_COLUMN = 0;
    private static final int CONTINENT_COLUMN = 1;
    private static final int POPULATION_COLUMN = 2;
    private static final int COLUMN_NUMBER = 3;
    ArrayList<MetropolisesInfo> metropolises;
    MetropolisesDataBase database;
    public MetropolisesJTable(String databaseName, String tableName) throws SQLException, ClassNotFoundException {
        metropolises = new ArrayList<>();
        database = new MetropolisesDataBase(databaseName, tableName);
    }
    /**
     * @param metropolis
     * @param continent
     * @param population
     * @param wantLarger
     * @param wantExact
     * Searches metropolises for certain parameters and updates table.
     * @throws SQLException
     */
    public void search(String metropolis, String continent, String population,
                       boolean wantLarger, boolean wantExact) throws SQLException {
        metropolises = database.searchMetropolises(metropolis, continent, population, wantLarger, wantExact);
        fireTableDataChanged();
    }
    /**
     * @param metropolis
     * @param continent
     * @param population
     * Adds new metropolis to the SQLtable and updates table.
     * @throws SQLException
     */
    public void add(String metropolis, String continent, String population) throws SQLException {
        MetropolisesInfo newMetropolis = new MetropolisesInfo(metropolis, continent, population);
        metropolises.add(newMetropolis);
        database.addMetropolis(metropolis, continent, population);
        fireTableRowsInserted(metropolises.size()-1, metropolises.size()-1);
    }

    @Override
    public int getRowCount() {
        return metropolises.size();
    }

    @Override
    public int getColumnCount() {
        return COLUMN_NUMBER;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        if(rowIndex >= getRowCount())
            return null;
        if(columnIndex == METROPOLIS_COLUMN)
            return metropolises.get(rowIndex).getMetropolis();
        if(columnIndex == CONTINENT_COLUMN)
            return metropolises.get(rowIndex).getContinent();
        if(columnIndex == POPULATION_COLUMN)
            return metropolises.get(rowIndex).getPopulation();
        return null;
    }

    @Override
    public String getColumnName(int col){
        if(col == METROPOLIS_COLUMN)
            return "Metropolis";
        if(col == CONTINENT_COLUMN)
            return "Continent";
        if(col == POPULATION_COLUMN)
            return "Population";
        return null;
    }
}
