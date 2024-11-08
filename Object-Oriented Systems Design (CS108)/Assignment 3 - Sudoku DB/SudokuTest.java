import junit.framework.TestCase;

public class SudokuTest extends TestCase {

    public static final int SIZE = 9;  // size of the whole 9x9 puzzle
    public static final int PART = 3;  // size of each 3x3 part
    public static final int[][] easyGrid = Sudoku.stringsToGrid(
            "1 6 4 0 0 0 0 0 2",
            "2 0 0 4 0 3 9 1 0",
            "0 0 5 0 8 0 4 0 7",
            "0 9 0 0 0 6 5 0 0",
            "5 0 0 1 0 2 0 0 8",
            "0 0 8 9 0 0 0 3 0",
            "8 0 9 0 4 0 2 0 0",
            "0 7 3 5 0 9 0 0 1",
            "4 0 0 0 0 0 6 7 9");
    public static final int[][] mediumGrid = Sudoku.stringsToGrid(
            "530070000",
            "600195000",
            "098000060",
            "800060003",
            "400803001",
            "700020006",
            "060000280",
            "000419005",
            "000080079");
    public static final int[][] hardGrid = Sudoku.stringsToGrid(
            "3 7 0 0 0 0 0 8 0",
            "0 0 1 0 9 3 0 0 0",
            "0 4 0 7 8 0 0 0 3",
            "0 9 3 8 0 0 0 1 2",
            "0 0 0 0 4 0 0 0 0",
            "5 2 0 0 0 6 7 9 0",
            "6 0 0 0 2 1 0 4 0",
            "0 0 0 5 3 0 9 0 0",
            "0 3 0 0 0 0 0 5 1");

    public static final int[][] hardGridSol0 = Sudoku.stringsToGrid(
            "3 6 0 0 0 0 0 8 0",
            "0 0 1 0 9 3 0 0 0",
            "0 4 0 7 8 0 0 0 3",
            "0 9 3 8 0 0 0 1 2",
            "0 0 0 0 4 0 0 0 0",
            "5 2 0 0 0 6 7 9 0",
            "6 0 0 0 2 1 0 4 0",
            "0 0 0 5 3 0 9 0 0",
            "0 3 0 0 0 0 0 5 1");
    public static final int[][] hardGridSol5 = Sudoku.stringsToGrid(
            "3 5 0 0 0 0 0 8 0",
            "0 0 1 0 9 3 0 0 0",
            "0 4 0 7 8 0 0 0 3",
            "0 9 3 8 0 0 0 1 2",
            "0 0 0 0 4 0 0 0 0",
            "5 2 0 0 0 6 7 9 0",
            "6 0 0 0 2 1 0 4 0",
            "0 0 0 5 3 0 9 0 0",
            "0 3 0 0 0 0 0 5 1");

    public static final int[][] hardGridSol6 = Sudoku.stringsToGrid(
            "3 0 0 0 0 0 0 8 0",
            "0 0 1 0 9 3 0 0 0",
            "0 4 0 7 8 0 0 0 3",
            "0 9 3 8 0 0 0 1 2",
            "0 0 0 0 4 0 0 0 0",
            "5 2 0 0 0 6 7 9 0",
            "6 0 0 0 2 1 0 4 0",
            "0 0 0 5 3 0 9 0 0",
            "0 3 0 0 0 0 0 5 1");

    private int[][] numGrid;
    private String numGridString;
    private int[][] grid;
    private Sudoku sudoku;
    protected void setUp() throws Exception {
        super.setUp();
        makeNumGridString();
    }

    private void makeNumGridString() {
        numGridString = "123456789";
        for(int i = 0; i < 8; i++)
            for(int j = 0; j < 9; j++)
                numGridString += "0";
        numGrid = Sudoku.textToGrid(numGridString);
    }

    public void testEasySudoku(){
        sudoku = new Sudoku(easyGrid);
        assertEquals(sudoku.solve(), 1);
        grid = sudoku.getGrid();
        assertTrue(sudokuChecker());
    }
    public void testMediumSudoku(){
        sudoku = new Sudoku(mediumGrid);
        assertEquals(sudoku.solve(), 1);
        grid = sudoku.getGrid();
        assertTrue(sudokuChecker());
    }

    public void testHardSudokuVariations(){
        sudoku = new Sudoku(hardGrid);
        assertEquals(sudoku.solve(), 1);
        grid = sudoku.getGrid();
        assertTrue(sudokuChecker());
        sudoku = new Sudoku(hardGridSol0);
        assertEquals(sudoku.solve(), 0);
        assertEquals(sudoku.getSolutionText(), "");
        sudoku = new Sudoku(hardGridSol5);
        assertEquals(sudoku.solve(), 5);
        grid = sudoku.getGrid();
        assertTrue(sudokuChecker());
        sudoku = new Sudoku(hardGridSol6);
        assertEquals(sudoku.solve(), 6);
        grid = sudoku.getGrid();
        assertTrue(sudokuChecker());
    }

    public void testSudokuLotSolution(){
        sudoku = new Sudoku(numGrid);
        assertEquals(sudoku.solve(), 100);
        fillGrid(sudoku.getSolutionText());
        assertTrue(sudokuChecker());
        sudoku.getElapsed();
        try{
            grid = Sudoku.textToGrid("1");
        }catch (RuntimeException e){
            assertEquals("Needed 81 numbers, but got:1", e.getMessage());
        }
    }

    private void fillGrid(String solutionText) {
        grid = new int[9][9];
        int ind = 0;
        for(int i = 0; i < 9; i++){
            for(int j = 0; j < 9; j++){
                grid[i][j] = solutionText.charAt(ind) - '0';
                ind += 2;
            }
        }
    }

    private boolean sudokuChecker(){
        int[] tmpRowCheck = new int[SIZE+1];
        int[] tmpColCheck = new int[SIZE+1];
        for(int i = 0; i < SIZE; i++){
            for(int j = 0; j <= SIZE; j++) {
                tmpRowCheck[j] = 0;
                tmpColCheck[j] = 0;
            }
            for(int j = 0; j < SIZE; j++)
                tmpRowCheck[grid[i][j]]++;
            for(int j = 0; j < SIZE; j++)
                tmpColCheck[grid[j][i]]++;
            for(int j = 1; j <= SIZE; j++)
                if(tmpRowCheck[j] > 1)
                    return false;
            for(int j = 1; j <= SIZE; j++)
                if(tmpColCheck[j] > 1)
                    return false;
        }
        int[] tmpBoxCheck = new int[SIZE+1];
        for(int i = 0; i < PART; i++) {
            for (int j = 0; j < PART; j++) {
                for(int k = 0; k <= SIZE; k++)
                    tmpBoxCheck[k] = 0;
                for(int k = 0; k < PART; k++) {
                    for (int t = 0; t < PART; t++) {
                        tmpBoxCheck[grid[i*PART + k][j*PART + t]]++;
                    }
                }
                for(int k = 1; k <= SIZE; k++)
                    if(tmpBoxCheck[k] > 1)
                        return false;
            }
        }
        return true;
    }
}
