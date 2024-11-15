import java.util.*;

/*
 * Encapsulates a Sudoku grid to be solved.
 * CS108 Stanford.
 */
public class Sudoku {
	// Provided grid data for main/testing
	// The instance variable strategy is up to you.
	
	// Provided easy 1 6 grid
	// (can paste this text into the GUI too)
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
	
	
	// Provided medium 5 3 grid
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
	
	// Provided hard 3 7 grid
	// 1 solution this way, 6 solutions if the 7 is changed to 0
	public static final int[][] hardGrid = Sudoku.stringsToGrid(
	"3 0 0 0 0 0 0 8 0",
	"0 0 1 0 9 3 0 0 0",
	"0 4 0 7 8 0 0 0 3",
	"0 9 3 8 0 0 0 1 2",
	"0 0 0 0 4 0 0 0 0",
	"5 2 0 0 0 6 7 9 0",
	"6 0 0 0 2 1 0 4 0",
	"0 0 0 5 3 0 9 0 0",
	"0 3 0 0 0 0 0 5 1");
	
	private int[][] grid;
	public static final int SIZE = 9;  // size of the whole 9x9 puzzle
	public static final int PART = 3;  // size of each 3x3 part
	public static final int MAX_SOLUTIONS = 100;
	
	// Provided various static utility methods to
	// convert data formats to int[][] grid.
	
	/**
	 * Returns a 2-d grid parsed from strings, one string per row.
	 * The "..." is a Java 5 feature that essentially
	 * makes "rows" a String[] array.
	 * (provided utility)
	 * @param rows array of row strings
	 * @return grid
	 */
	public static int[][] stringsToGrid(String... rows) {
		int[][] result = new int[rows.length][];
		for (int row = 0; row<rows.length; row++) {
			result[row] = stringToInts(rows[row]);
		}
		return result;
	}
	
	
	/**
	 * Given a single string containing 81 numbers, returns a 9x9 grid.
	 * Skips all the non-numbers in the text.
	 * (provided utility)
	 * @param text string of 81 numbers
	 * @return grid
	 */
	public static int[][] textToGrid(String text) {
		int[] nums = stringToInts(text);
		if (nums.length != SIZE*SIZE) {
			throw new RuntimeException("Needed 81 numbers, but got:" + nums.length);
		}
		
		int[][] result = new int[SIZE][SIZE];
		int count = 0;
		for (int row = 0; row<SIZE; row++) {
			for (int col=0; col<SIZE; col++) {
				result[row][col] = nums[count];
				count++;
			}
		}
		return result;
	}
	
	
	/**
	 * Given a string containing digits, like "1 23 4",
	 * returns an int[] of those digits {1 2 3 4}.
	 * (provided utility)
	 * @param string string containing ints
	 * @return array of ints
	 */
	public static int[] stringToInts(String string) {
		int[] a = new int[string.length()];
		int found = 0;
		for (int i=0; i<string.length(); i++) {
			if (Character.isDigit(string.charAt(i))) {
				a[found] = Integer.parseInt(string.substring(i, i+1));
				found++;
			}
		}
		int[] result = new int[found];
		System.arraycopy(a, 0, result, 0, found);
		return result;
	}


	// Provided -- the deliverable main().
	// You can edit to do easier cases, but turn in
	// solving hardGrid.

	@Override
	public String toString(){
		StringBuilder gridStr = new StringBuilder("");
		for(int i = 0; i < SIZE; i++){
			for(int j = 0; j < SIZE; j++){
				gridStr.append(grid[i][j]);
				if(j != SIZE - 1)
					gridStr.append(" ");
			}
			if(i != SIZE - 1)
				gridStr.append("\n");
		}
		return gridStr.toString();
	}

	private ArrayList<Spot> spots;
	/**
	 * Sets up based on the given ints.
	 */
	public Sudoku(int[][] ints) {
		grid = ints;
		spots = new ArrayList<>();
	}
	private void sortSpots(){
		for(int i = 0; i < SIZE; i++)
			for(int j = 0; j < SIZE; j++)
				if(grid[i][j] == 0)
					spots.add(new Spot(i, j));
		Collections.sort(spots);
	}
	int solveCount;
	String solveText;
	/**
	 * Solves the puzzle, invoking the underlying recursive search.
	 */
	public int solve() {
		start = System.currentTimeMillis();
		solveCount = 0;
		sortSpots();
		solver(0);
		end = System.currentTimeMillis();
		return solveCount;
	}

	private void solver(int spotInd){
		if(spotInd == spots.size()) {
			solveCount++;
			if(solveCount == 1)
				solveText = toString();
			return;
		}
		Spot currSpot = spots.get(spotInd);
		currSpot.fillLegalNums();
		for(int i = 0; i < currSpot.size; i++){
			currSpot.set(currSpot.legalNums.get(i));
			if(solveCount < MAX_SOLUTIONS) {
				solver(spotInd + 1);
			}
			currSpot.set(0);
		}
	}
	
	public String getSolutionText() {
		if(solveCount == 0)
			return "";
		return solveText;
	}

	int[][] getGrid(){
		return grid;
	}
	long start;
	long end;
	public long getElapsed() {
		return end - start;
	}


	private class Spot implements Comparable<Spot>{
		private int x;
		private int y;

		private int size;

		private ArrayList<Integer> legalNums;
		public Spot(int x, int y){
			this.x = x;
			this.y = y;
			legalNums = new ArrayList<>();
			fillLegalNums();
		}
		private void fillLegalNums(){
			legalNums.clear();
			Boolean[] tmpArr = new Boolean[SIZE+1];
			for(int i = 0; i <= SIZE; i++)
				tmpArr[i] = false;
			for(int i = 0; i < SIZE; i++)
				tmpArr[grid[x][i]] = true;
			for(int i = 0; i < SIZE; i++)
				tmpArr[grid[i][y]] = true;
			int bigX = (x / PART) * PART;
			int bigY = (y / PART) * PART;
			for(int i = 0; i < PART; i++)
				for(int j = 0; j < PART; j++)
					tmpArr[grid[bigX+i][bigY+j]] = true;
			for(int i = 1; i <= SIZE; i++)
				if(!tmpArr[i])
					legalNums.add(i);
			size = legalNums.size();
		}
		private void set(int num){
			grid[x][y] = num;
		}
		@Override
		public int compareTo(Spot o) {
			return this.size - o.size;
		}
	}
}
