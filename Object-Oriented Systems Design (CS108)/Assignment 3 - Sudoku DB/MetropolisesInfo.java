import java.sql.SQLException;

public class MetropolisesInfo {
    private String metropolis;
    private String continent;
    private String population;
    public MetropolisesInfo(String metropolis, String continent, String population){
        this.metropolis = metropolis;
        this.continent = continent;
        this.population = population;
    }
    /**
     * Returns metropolis' name;
     */
    public String getMetropolis(){
        return metropolis;
    }
    /**
     * Returns continent's name;
     */
    public String getContinent(){
        return continent;
    }
    /**
     * Returns number of population;
     */
    public String getPopulation(){
        return population;
    }
}
