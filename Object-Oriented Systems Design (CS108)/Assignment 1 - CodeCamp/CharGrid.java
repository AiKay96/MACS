// HW1 2-d array Problems
// CharGrid encapsulates a 2-d grid of chars and supports
// a few operations on the grid.

public class CharGrid {
	private char[][] grid;

	/**
	 * Constructs a new CharGrid with the given grid.
	 * Does not make a copy.
	 * @param grid
	 */
	public CharGrid(char[][] grid) {
		this.grid = grid;
	}
	
	/**
	 * Returns the area for the given char in the grid. (see handout).
	 * @param ch char to look for
	 * @return area for given char
	 */
	public int charArea(char ch) {
		int upInd = -1;
		int downInd = -1;
		int leftInd = -1;
		int rightInd = -1;
		boolean found = false;
		for(int i = 0; i < grid.length; i++){
			for(int j = 0; j < grid[0].length; j++){
				if(grid[i][j] == ch){
					upInd = i;
					downInd = i;
					leftInd = j;
					rightInd = j;
					found = true;
					break;
				}
			}
			if(found)
				break;
		}
		if(upInd == -1)
			return 0;
		for(int i = upInd; i < grid.length; i++) {
			for (int j = 0; j < grid[0].length; j++) {
				if(grid[i][j] == ch) {
					leftInd = Math.min(j, leftInd);
					rightInd = Math.max(j, rightInd);
					downInd = i;
				}
			}
		}
		return (rightInd - leftInd + 1)*(downInd - upInd + 1);
	}
	private boolean inBounds(int x, int y){
		if(x >= 0 && x < grid.length && y >= 0 && y < grid[0].length)
			return true;
		return false;
	}
	private boolean checkPlus(int i, int j){
		char mid = grid[i][j];
		if(mid == ' ')
			return false;
		int x = i;
		int y = j;
		//check right hand
		while(inBounds(i, y) && mid == grid[i][y])
			y++;
		int len = y - j;
		if(len == 1)
			return false;
		y = j;
		//check left hand
		while(inBounds(i, y) && mid == grid[i][y])
			y--;
		if(j - y != len)
			return false;
		//check bottom hand
		while(inBounds(x, j) && mid == grid[x][j])
			x++;
		if(x - i != len)
			return false;
		x = i;
		//check upper hand
		while(inBounds(x, j) && mid == grid[x][j])
			x--;
		if(i - x != len)
			return false;
		return true;
	}
	/**
	 * Returns the count of '+' figures in the grid (see handout).
	 * @return number of + in grid
	 */
	public int countPlus() {
		int count = 0;
		for(int i = 1; i < grid.length; i++) {
			for (int j = 1; j < grid[0].length; j++) {
				if(checkPlus(i, j))
					count++;
			}
		}
		return count;
	}
	
}
