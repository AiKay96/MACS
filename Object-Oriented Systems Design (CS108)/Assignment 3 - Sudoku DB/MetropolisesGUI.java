import javax.swing.*;
import javax.swing.border.TitledBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.SQLException;

public class MetropolisesGUI extends JFrame {
    JPanel panel;
    JTextField metropolisField;
    JTextField continentField;
    JTextField populationField;
    JButton addButton;
    JButton searchButton;
    JComboBox populationCombo;
    JComboBox matchCombo;
    MetropolisesJTable metropolisesTable;
    String databaseName;
    String tableName;
    public MetropolisesGUI(String databaseName, String tableName) throws SQLException, ClassNotFoundException {
        super("Metropolis Viewer");

        this.databaseName = databaseName;
        this.tableName = tableName;

        panel = new JPanel();
        panel.setLayout(new BorderLayout(4, 4));

        setUpUpperPart();
        setUpRightPart();
        setUpCenter();

        add(panel);
        addingListeners();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        pack();
        setVisible(true);
    }
    /**
     * Creates and sets up center to show table.
     * @throws SQLException
     * @throws ClassNotFoundException
     */
    private void setUpCenter() throws SQLException, ClassNotFoundException {
        metropolisesTable = new MetropolisesJTable(databaseName, tableName);
        JTable table = new JTable(metropolisesTable);
        JScrollPane scroll = new JScrollPane(table);
        panel.add(scroll, BorderLayout.CENTER);
    }
    /**
     * Creates and sets up righter part to show buttons and choose options for client.
     */
    private void setUpRightPart(){
        JPanel rightPanel = new JPanel();
        rightPanel.setPreferredSize(new Dimension(200, 600));
        rightPanel.setLayout(new GridLayout(6, 1));

        JPanel buttonPanel = new JPanel();
        buttonPanel.setLayout(new GridLayout(2, 1));
        addButton = new JButton("Add");
        buttonPanel.add(addButton);

        searchButton = new JButton("Search");
        buttonPanel.add(searchButton);

        rightPanel.add(buttonPanel);

        JPanel searchPanel = new JPanel();
        searchPanel.setLayout(new BoxLayout(searchPanel, BoxLayout.Y_AXIS));
        searchPanel.setBorder(new TitledBorder("Search Options"));

        populationCombo = new JComboBox<>(new String[]{"Population Larger Than", "Population Smaller Than"});
        searchPanel.add(populationCombo);

        matchCombo = new JComboBox<>(new String[]{"Exact Match", "Partial Match"});
        searchPanel.add(matchCombo);

        rightPanel.add(searchPanel);

        panel.add(rightPanel, BorderLayout.EAST);
    }
    /**
     * Creates and sets up upper part to show text fields for add and search.
     */
    private void setUpUpperPart(){
        JPanel upperPanel = new JPanel();
        upperPanel.setLayout(new GridLayout(1, 3, 20, 20));

        JPanel metropolisPanel = new JPanel();
        metropolisPanel.setLayout(new BoxLayout(metropolisPanel, BoxLayout.X_AXIS));
        JLabel metropolisLabel = new JLabel("Metropolis:");
        metropolisField = new JTextField();

        metropolisPanel.add(metropolisLabel);
        metropolisPanel.add(metropolisField);
        upperPanel.add(metropolisPanel);

        JPanel continentPanel = new JPanel();
        continentPanel.setLayout(new BoxLayout(continentPanel, BoxLayout.X_AXIS));
        JLabel continentLabel = new JLabel("Continent:");
        continentField = new JTextField();

        continentPanel.add(continentLabel);
        continentPanel.add(continentField);
        upperPanel.add(continentPanel);

        JPanel populationPanel = new JPanel();
        populationPanel.setLayout(new BoxLayout(populationPanel, BoxLayout.X_AXIS));
        JLabel populationLabel = new JLabel("Population:");
        populationField = new JTextField();

        populationPanel.add(populationLabel);
        populationPanel.add(populationField);
        upperPanel.add(populationPanel);

        panel.add(upperPanel, BorderLayout.NORTH);
    }
    /**
     * Adds listeners and calls functions for certain JObjects.
     */
    private void addingListeners(){
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    if(!metropolisField.getText().equals("") && !continentField.getText().equals("")
                            && !populationField.getText().equals(""))
                        metropolisesTable.add(metropolisField.getText(), continentField.getText(), populationField.getText());
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                try {
                    metropolisesTable.search(metropolisField.getText(), continentField.getText(), populationField.getText(),
                            populationCombo.getSelectedIndex() == 0, matchCombo.getSelectedIndex() == 0);
                } catch (SQLException ex) {
                    throw new RuntimeException(ex);
                }
            }
        });
    }
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        // GUI Look And Feel
        // Do this incantation at the start of main() to tell Swing
        // to use the GUI LookAndFeel of the native platform. It's ok
        // to ignore the exception.
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ignored) { }

        MetropolisesGUI view = new MetropolisesGUI("OOP_DATABASE", "metropolises");
    }
}
