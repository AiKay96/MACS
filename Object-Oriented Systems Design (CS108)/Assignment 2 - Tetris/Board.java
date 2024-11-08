// Board.java

/**
 CS108 Tetris Board.
 Represents a Tetris board -- essentially a 2-d grid
 of booleans. Supports tetris pieces and row clearing.
 Has an "undo" feature that allows clients to add and remove pieces efficiently.
 Does not do any drawing or have any idea of pixels. Instead,
 just represents the abstract 2-d board.
*/
public class Board	{
	// Some ivars are stubbed out for you:
	private int width;
	private int height;
	private boolean[][] grid;
    private boolean[][] dataGrid;
    private int[] rows;
    private int[] dataRows;
    private int[] columns;
    private int[] dataColumns;
	private boolean DEBUG = true;
	boolean committed;
	
	
	// Here a few trivial methods are provided:
	
	/**
	 Creates an empty board of the given width and height
	 measured in blocks.
	*/
	public Board(int width, int height) {
		this.width = width;
		this.height = height;
		grid = new boolean[width][height];
        dataGrid = new boolean[width][height];
        rows = new int[height];
        dataRows = new int[height];
        columns = new int[width];
        dataColumns = new int[width];
		committed = true;
	}
	
	
	/**
	 Returns the width of the board in blocks.
	*/
	public int getWidth() {
		return width;
	}
	
	
	/**
	 Returns the height of the board in blocks.
	*/
	public int getHeight() {
		return height;
	}
	
	
	/**
	 Returns the max column height present in the board.
	 For an empty board this is 0.
	*/
	public int getMaxHeight() {
		int maxH = 0;
		for(int i = 0; i < width; i++)
			maxH = Math.max(maxH, columns[i]);
		return maxH;
	}
	/**
	 Checks the board for `getRowWidth(y)`
	 */
	private void widthCheck(){
		for(int j = 0; j < height; j++){
			int count = 0;
			for(int i = 0; i < width; i++)
				if(grid[i][j])
					count++;
			if(count != getRowWidth(j))
				throw new RuntimeException("Wrong width on row: " + j);
		}
	}
	/**
	 Checks the board for `getColumnHeight(x)`
	 */
	private void heightCheck(){
		for(int i = 0; i < width; i++){
			for(int j = height - 1; j >= 0; j--){
				if(grid[i][j]){
					if(j + 1 != getColumnHeight(i))
						throw new RuntimeException("Wrong height on column: " + i + "\n" + "Expected: " + (j + 1) + " Your answer: " + getColumnHeight(i) );
					break;
				}
			}
		}
	}

	/**
	 Checks the board for `getMaxHeight()`
	 */
	private void maxHeightCheck(){
		int maxHC = 0;
		for(int i = 0; i < width; i++)
			maxHC = Math.max(maxHC, columns[i]);
		if(maxHC != getMaxHeight())
			throw new RuntimeException("Wrong maximum height");
	}
	/**
	 Checks the board for internal consistency -- used
	 for debugging.
	*/
	public void sanityCheck() {
		if (DEBUG) {
			widthCheck();
			heightCheck();
			maxHeightCheck();
		}
	}
	
	/**
	 Given a piece and an x, returns the y
	 value where the piece would come to rest
	 if it were dropped straight down at that x.
	 
	 <p>
	 Implementation: use the skirt and the col heights
	 to compute this fast -- O(skirt length).
	*/
	public int dropHeight(Piece piece, int x) {
		int[] skirt = piece.getSkirt();
		int ans = 0;
		for(int i = 0; i < piece.getWidth(); i++){
			ans = Math.max(ans, columns[x+i] - skirt[i]);
		}
		return ans;
	}
	
	
	/**
	 Returns the height of the given column --
	 i.e. the y value of the highest block + 1.
	 The height is 0 if the column contains no blocks.
	*/
	public int getColumnHeight(int x) {
		return columns[x];
	}
	
	
	/**
	 Returns the number of filled blocks in
	 the given row.
	*/
	public int getRowWidth(int y) {
		 return rows[y];
	}
	
	
	/**
	 Returns true if the given block is filled in the board.
	 Blocks outside of the valid width/height area
	 always return true.
	*/
	public boolean getGrid(int x, int y) {
		return grid[x][y];
	}
	
	
	public static final int PLACE_OK = 0;
	public static final int PLACE_ROW_FILLED = 1;
	public static final int PLACE_OUT_BOUNDS = 2;
	public static final int PLACE_BAD = 3;

	/**
	 Checks if point is on the grid. Returns false if coordinates are out of grid.
	 */
    private boolean inBounds(int x, int y){
        if(x < 0 || y < 0 || x > width || y > height)
            return false;
        return true;
    }

	/**
	 Checks if piece every point is empty. Returns false if it is not.
	 */
	private boolean badPlacement(Piece piece, int x, int y){
		int[] skirt = piece.getSkirt();
		boolean flag = false;
		for(int i = 0; i < piece.getWidth(); i++){
			if(y + skirt[i] < columns[x + i]){
				flag = true;
				break;
			}
		}
		return flag;
	}

	/**
	 Places piece on the grid. Returns true, if one or more row
	 gets filled.
	 */
	private boolean filledRow(Piece piece, int x, int y){
		TPoint[] points = piece.getBody();
		boolean flag = false;
		for(int i = 0; i < points.length; i++){
			if(rows[y+points[i].y] == width)
				flag = true;
			if(grid[x+points[i].x][y+points[i].y])
				continue;
			grid[x+points[i].x][y+points[i].y] = true;
			rows[y+points[i].y]++;
			columns[x+points[i].x] = Math.max(columns[x+points[i].x],y+points[i].y+1);
			if(rows[y+points[i].y] == width)
				flag = true;
		}
		return flag;
	}

	/**
	 Attempts to add the body of a piece to the board.
	 Copies the piece blocks into the board grid.
	 Returns PLACE_OK for a regular placement, or PLACE_ROW_FILLED
	 for a regular placement that causes at least one row to be filled.

	 <p>Error cases:
	 A placement may fail in two ways. First, if part of the piece may falls out
	 of bounds of the board, PLACE_OUT_BOUNDS is returned.
	 Or the placement may collide with existing blocks in the grid
	 in which case PLACE_BAD is returned.
	 In both error cases, the board may be left in an invalid
	 state. The client can use undo(), to recover the valid, pre-place state.
	 */
	public int place(Piece piece, int x, int y) {
		// flag !committed problem
		if (!committed) throw new RuntimeException("place commit problem");

		committed = false;

		if(!inBounds(x,y) || !inBounds(x + piece.getWidth(), y + piece.getHeight()))
		    return PLACE_OUT_BOUNDS;

        if(badPlacement(piece, x, y)) {
			filledRow(piece, x, y);
			return PLACE_BAD;
		}

		if(filledRow(piece, x, y))
			return PLACE_ROW_FILLED;

		return PLACE_OK;
	}

	/**
	 Finds the lowest filled row.
	 */
	private int findFirstFullRow(){
		for(int i = 0; i < height; i++)
			if(rows[i] == width)
				return i;
		return -1;
	}

	/**
	 Deletes only one row.
	 */
	private void clearOneRow(int y){
		for(int i = 0; i < width; i++)
			grid[i][y] = false;
		rows[y] = 0;
	}

	/**
	 Updates column heights after clearing rows.
	 */
	private void updateHeights(){
		for(int i = 0; i < width; i++){
			int h = height - 1;
			while(h >= 1 && !grid[i][h])
				h--;
			if(grid[i][h])
				columns[i] = h+1;
			else
				columns[i] = h;
		}
	}

	/**
	 Updates grid rows and row widths.
	 */
	private void updateWidths(int toRow, int fromRow){
		int rowW = 0;
		for(int i = 0; i < width; i++){
			grid[i][toRow] = grid[i][fromRow];
			if(grid[i][toRow])
				rowW++;
		}
		rows[toRow] = rowW;
	}
	private int updateGrid(){
		int toRow = findFirstFullRow();
		if(toRow == -1)
			return 0;
		int rowsCleared = 0;
		int fromRow = toRow;
		while(fromRow <= height){
			//Skipping filled rows
			while(fromRow < height && rows[fromRow] == width){
				fromRow++;
				rowsCleared++;
			}
			//Case if we reach top
			if(fromRow == height) {
				for (int i = toRow; i < fromRow; i++)
					clearOneRow(i);
				break;
			}
			updateWidths(toRow, fromRow);
			toRow++;
			fromRow++;
		}
		return rowsCleared;
	}
	/**
	 Deletes rows that are filled all the way across, moving
	 things above down. Returns the number of rows cleared.
	*/
	public int clearRows() {
		int rowsCleared = updateGrid();
		if(rowsCleared == 0)
			return 0;
		updateHeights();
		sanityCheck();
		committed = false;
		return rowsCleared;
	}



	/**
	 Reverts the board to its state before up to one place
	 and one clearRows();
	 If the conditions for undo() are not met, such as
	 calling undo() twice in a row, then the second undo() does nothing.
	 See the overview docs.
	*/
	public void undo() {
		if(committed)
			return;
		boolean[][] tmpGrid = grid;
		int[] tmpColumns = columns;
		int[] tmpRows = rows;
		grid = dataGrid;
		columns = dataColumns;
		rows = dataRows;
		dataGrid = tmpGrid;
		dataColumns = tmpColumns;
		dataRows = tmpRows;
		commit();
	}
	
	
	/**
	 Puts the board in the committed state.
	*/
	public void commit() {
		for(int i = 0; i < width; i++)
			if (height >= 0) System.arraycopy(grid[i], 0, dataGrid[i], 0, height);
		if (width >= 0) System.arraycopy(columns, 0, dataColumns, 0, width);
		if (height >= 0) System.arraycopy(rows, 0, dataRows, 0, height);
		committed = true;
	}


	
	/*
	 Renders the board state as a big String, suitable for printing.
	 This is the sort of print-obj-state utility that can help see complex
	 state change over time.
	 (provided debugging utility) 
	 */
	public String toString() {
		StringBuilder buff = new StringBuilder();
		for (int y = height-1; y>=0; y--) {
			buff.append('|');
			for (int x=0; x<width; x++) {
				if (getGrid(x,y)) buff.append('+');
				else buff.append(' ');
			}
			buff.append("|\n");
		}
		for (int x=0; x<width+2; x++) buff.append('-');
		return(buff.toString());
	}
}


