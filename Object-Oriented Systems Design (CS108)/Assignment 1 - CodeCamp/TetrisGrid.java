//
// TetrisGrid encapsulates a tetris board and has
// a clearRows() capability.

public class TetrisGrid {

	private boolean[][] grid;
	/**
	 * Constructs a new instance with the given grid.
	 * Does not make a copy.
	 * @param grid
	 */
	public TetrisGrid(boolean[][] grid)  {
		this.grid = grid;
	}
	
	
	/**
	 * Does row-clearing on the grid (see handout).
	 */
	public void clearRows() {
		int x = 0;
		for(int j = 0; j < grid[0].length; j++){
			boolean row = true;
			for(int i = 0; i < grid.length; i++)
				row &= grid[i][j];
			if(!row){
				for(int i = 0; i < grid.length; i++)
					grid[i][x] = grid[i][j];
				x++;
			}
		}
		for(int j = x; j < grid[0].length; j++)
			for(int i = 0; i < grid.length; i++)
				grid[i][j] = false;
	}
	
	/**
	 * Returns the internal 2d grid array.
	 * @return 2d grid array
	 */
	boolean[][] getGrid() {
		return grid;
	}
}
