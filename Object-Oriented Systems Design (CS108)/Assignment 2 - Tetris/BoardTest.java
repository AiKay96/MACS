import junit.framework.TestCase;

import java.util.Arrays;


public class BoardTest extends TestCase {
	Board b;
	Piece pyr1, pyr2, pyr3, pyr4, s, sRotated;
	Piece[] pc;

	Board bplace1, bplace2, bplace3;

	Board bdrop1, bdrop2;

	Board bclear1, bclear2, bclear3;

	Board undo1, undo2;

	boolean[][] testGrid1, testGrid2;
	// This shows how to build things in setUp() to re-use
	// across tests.

	// In this case, setUp() makes shapes,
	// and also a 3X6 board, with pyr placed at the bottom,
	// ready to be used by tests.

	protected void setUp() throws Exception {
		b = new Board(3, 6);

		pyr1 = new Piece(Piece.PYRAMID_STR);
		pyr2 = pyr1.computeNextRotation();
		pyr3 = pyr2.computeNextRotation();
		pyr4 = pyr3.computeNextRotation();

		s = new Piece(Piece.S1_STR);
		sRotated = s.computeNextRotation();

		b.place(pyr1, 0, 0);

		bplace1 = new Board(5, 5);
		bplace2 = new Board(5, 5);
		bplace3 = new Board(5, 5);

		bclear1 = new Board(4, 5);
		bclear2 = new Board(5, 5);
		bclear3 = new Board(10, 10);

		bdrop1 = new Board(5, 5);
		bdrop2 = new Board(10, 10);

		pc = s.getPieces();

		undo1 = new Board(4, 4);
		undo2 = new Board(5, 5);
	}

	public void testUndo(){
		assertEquals(Board.PLACE_OK, undo1.place(pc[Piece.SQUARE], 0, 0));
		undo1.commit();
		assertEquals(Board.PLACE_ROW_FILLED, undo1.place(pc[Piece.SQUARE], 2, 0));
		undo1.commit();
		assertEquals(Board.PLACE_BAD, undo1.place(pc[Piece.SQUARE], 1, 0));
		undo1.undo();
		undo1.clearRows();

		assertEquals(Board.PLACE_OUT_BOUNDS, undo2.place(pc[Piece.STICK].fastRotation(), 3, 0));
		undo2.undo();
		assertEquals(Board.PLACE_OK, undo2.place(pc[Piece.STICK].fastRotation(), 0, 0));
		undo2.commit();
		assertEquals(Board.PLACE_ROW_FILLED, undo2.place(pc[Piece.PYRAMID].fastRotation(), 3, 0));
		undo2.commit();
		String stringGrid = undo2.toString();
		assertEquals('+', stringGrid.charAt(stringGrid.length() - 10));
		undo2.clearRows();
		undo2.commit();
		stringGrid = undo2.toString();
		assertEquals('+', stringGrid.charAt(stringGrid.length() - 11));
		stringGrid = undo2.toString();
		undo2.undo();
		assertEquals(' ', stringGrid.charAt(stringGrid.length() - 12));
	}
	public void testDrop(){
		assertEquals(0, bdrop2.dropHeight(pc[6], 1));
		bdrop2.place(pc[6], 1, 0);
		bdrop2.commit();
		assertEquals(1, bdrop2.getRowWidth(1));
		assertEquals(2, bdrop2.getColumnHeight(2));
		assertEquals(2, bdrop2.dropHeight(pc[0], 2));
		bdrop2.place(pc[0], 2,2);
		bdrop2.commit();
		assertEquals(3, bdrop2.getRowWidth(0));
		assertEquals(6, bdrop2.getMaxHeight());
		assertEquals(5, bdrop2.dropHeight(pc[3], 0));
		bdrop2.place(pc[3], 0, 5);
		bdrop2.commit();
		assertEquals(6, bdrop2.getColumnHeight(0));
		assertEquals(7, bdrop2.getMaxHeight());
		assertEquals(3, bdrop2.getRowWidth(5));
		assertEquals(7, bdrop2.dropHeight(pc[5],0));
		bdrop2.place(pc[5], 0,7);
		bdrop2.commit();
	}
	public void testClear(){
		bclear1.place(pc[0].fastRotation(), 0, 0);
		bclear1.commit();
		int ans = bclear1.clearRows();
		bclear1.commit();
		for(int i = 0; i < bclear1.getWidth(); i++)
			assertFalse(bclear1.getGrid(i, 0));
		assertEquals(1, ans);
		bclear1.place(pc[5], 0, 0);
		bclear1.commit();
		bclear1.place(pc[5], 2, 0);
		bclear1.commit();
		ans = bclear1.clearRows();
		bclear1.commit();
		for(int i = 0; i < bclear1.getWidth(); i++)
			assertFalse(bclear1.getGrid(i, 0));
		for(int i = 0; i < bclear1.getWidth(); i++)
			assertFalse(bclear1.getGrid(i, 1));
		assertEquals(2, ans);
		bclear1.place(pc[6], 0, 0);
		bclear1.commit();
		ans = bclear1.clearRows();
		bclear1.commit();
		assertEquals(0, ans);
		assertTrue(bclear1.getGrid(1, 1));

		bclear2.place(pc[0].fastRotation(), 0, 0);
		bclear2.commit();
		bclear2.place(pc[4], 0, 1);
		bclear2.commit();
		bclear2.place(pc[0].fastRotation(), 0, 3);
		bclear2.commit();
		assertEquals(4, bclear2.getRowWidth(0));
		assertEquals(2, bclear2.getRowWidth(1));
		assertEquals(2, bclear2.getRowWidth(2));
		assertEquals(4, bclear2.getRowWidth(3));
		bclear2.place(pc[0], 4, 0);
		bclear2.commit();
		ans = bclear2.clearRows();
		bclear2.commit();
		assertEquals(3, bclear2.getRowWidth(0));
		assertEquals(3, bclear2.getRowWidth(1));
		assertEquals(0, bclear2.getRowWidth(2));
		assertEquals(2, ans);
		bclear3.place(pc[0].fastRotation(), 0, 0);
		bclear3.commit();
		bclear3.place(pc[0], 4, 0);
		bclear3.commit();
		bclear3.place(pc[0].fastRotation(), 5, 0);
		bclear3.commit();
		bclear3.place(pc[4].fastRotation(), 0, 1);
		bclear3.commit();
		bclear3.place(pc[5], 8, 1);
		bclear3.commit();
		bclear3.place(pc[0].fastRotation(), 0, 4);
		bclear3.commit();
		bclear3.place(pc[2].fastRotation(), 4, 3);
		bclear3.commit();
		bclear3.place(pc[2].fastRotation(), 7, 3);
		bclear3.commit();
		bclear3.place(pc[5], 2, 5);
		bclear3.commit();
		bclear3.place(pc[4].fastRotation(), 7, 5);
		bclear3.commit();
		bclear3.place(pc[0], 9, 5);
		bclear3.commit();
		bclear3.place(pc[6], 0, 7);
		bclear3.commit();
		bclear3.place(pc[0].fastRotation(), 3, 7);
		bclear3.commit();
		bclear3.place(pc[6].fastRotation().fastRotation(), 6, 7);
		bclear3.commit();
		ans = bclear3.clearRows();
		bclear3.commit();
		assertEquals(2, ans);
		int[] checkW = new int[] {9, 4, 5, 4, 4, 5, 5, 0, 0, 0};
		int[] checkH = new int[] {3, 7, 6, 6, 4, 1, 7, 7, 7, 7};
		for(int i = 0; i < bclear3.getWidth(); i++)
			assertEquals(checkW[i], bclear3.getRowWidth(i));
		for(int i = 0; i < bclear3.getHeight(); i++)
			assertEquals(checkH[i], bclear3.getColumnHeight(i));
	}
	public void testPlace(){
		bplace1.place(pc[0], 0, 0);
		bplace1.commit();
		assertEquals(4, bplace1.getColumnHeight(0));
		bplace1.place(pc[4].fastRotation(), 1, 0);
		bplace1.commit();
		assertEquals(4, bplace1.getMaxHeight());
		assertEquals(3, bplace1.getRowWidth(1));
		assertEquals(2, bplace1.getRowWidth(0));
		assertEquals(Board.PLACE_BAD, bplace1.place(pc[5], 2, 0));
		assertEquals(Board.PLACE_OUT_BOUNDS, bplace2.place(pc[1].fastRotation(), 4, 0));
		bplace3.place(pc[1].fastRotation(), 0, 0);
		bplace3.commit();
		assertEquals(Board.PLACE_ROW_FILLED, bplace3.place(pc[1], 3, 0));
		bplace3.commit();
		bplace3.place(pc[0].fastRotation(), 0, 3);
		assertTrue(bplace3.getGrid(0, 3));
		assertFalse(bplace3.getGrid(0, 2));
	}
	// Check the basic width/height/max after the one placement
	public void testSample1() {
		assertEquals(1, b.getColumnHeight(0));
		assertEquals(2, b.getColumnHeight(1));
		assertEquals(2, b.getMaxHeight());
		assertEquals(3, b.getRowWidth(0));
		assertEquals(1, b.getRowWidth(1));
		assertEquals(0, b.getRowWidth(2));
	}

	// Place sRotated into the board, then check some measures
	public void testSample2() {
		b.commit();
		int result = b.place(sRotated, 1, 1);
		assertEquals(Board.PLACE_OK, result);
		assertEquals(1, b.getColumnHeight(0));
		assertEquals(4, b.getColumnHeight(1));
		assertEquals(3, b.getColumnHeight(2));
		assertEquals(4, b.getMaxHeight());
	}

	// Make  more tests, by putting together longer series of
	// place, clearRows, undo, place ... checking a few col/row/max
	// numbers that the board looks right after the operations.
}
