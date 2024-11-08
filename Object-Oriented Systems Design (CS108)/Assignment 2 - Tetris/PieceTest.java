import junit.framework.TestCase;

import java.util.*;

/*
  Unit test for Piece class -- starter shell.
 */
public class PieceTest extends TestCase {
	// You can create data to be used in the your
	// test cases like this. For each run of a test method,
	// a new PieceTest object is created and setUp() is called
	// automatically by JUnit.
	// For example, the code below sets up some
	// pyramid and s pieces in instance variables
	// that can be used in tests.
	private Piece pyr1, pyr2, pyr3, pyr4;
	private Piece s, sRotated;

	private Piece Lvar1, Lvar2, Lvar3, Lvar4, Lvar5, Lvar6, Lvar7, st1;

	private Piece stick1, stick2, stick3, stick4;

	private Piece sq1, sq2;

	private Piece[] pc;
	protected void setUp() throws Exception {
		super.setUp();
		
		pyr1 = new Piece(Piece.PYRAMID_STR);
		pyr2 = pyr1.computeNextRotation();
		pyr3 = pyr2.computeNextRotation();
		pyr4 = pyr3.computeNextRotation();
		
		s = new Piece(Piece.S1_STR);
		sRotated = s.computeNextRotation();

		Lvar1 = new Piece("0 0 0 1 0 2 1 0");
		Lvar2 = new Piece("0 0 0 2 0 1 1 0");
		Lvar3 = new Piece("0 0 1 0 0 2 1 0");
		Lvar4 = new Piece("0 1 0 0 0 2 1 0");
		Lvar5 = new Piece("0 2 1 0 0 1 0 0");
		Lvar6 = new Piece(Piece.L2_STR);
		TPoint[] forLvar7 = new TPoint[4];
		TPoint[] forSt1 = new TPoint[4];
		forLvar7[0] = new TPoint(0, 1);
		forLvar7[1] = new TPoint(0, 2);
		forLvar7[2] = new TPoint(1, 1);
		forLvar7[3] = new TPoint(1, 0);
		for(int i = 0; i < 4; i++)
			forSt1[i] = new TPoint(0, i);
		Lvar7 = new Piece(forLvar7);
		st1 = new Piece(forSt1);

		stick1 = new Piece(Piece.STICK_STR);
		stick2 = stick1.computeNextRotation();
		stick3 = stick2.computeNextRotation();
		stick4 = stick3.computeNextRotation();

		sq1 = new Piece(Piece.SQUARE_STR);
		sq2 = sq1.computeNextRotation();

		pc = s.getPieces();
	}

	public void testError(){
		String str = "a";
		String[] strs = new String[3];
		strs[0] = Piece.PYRAMID_STR;
		strs[1] = "a";
		strs[2] = "0 1 0 0 0 0 0 0 k";
		for(int i = 0; i < 3; i++) {
			try{
				Piece test1 = new Piece(strs[i]);
			}catch (RuntimeException e){
				assertEquals("Could not parse x,y string:" + strs[i], e.getMessage());
			}
		}
	}
	public void testFastRotations(){
		assertTrue(pc[3].equals(pc[3].fastRotation().fastRotation()));
		assertTrue(pc[5].equals(pc[5].fastRotation()));
		assertTrue(Arrays.equals(new int[] {1, 0}, pc[6].fastRotation().getSkirt()));
		assertTrue(Arrays.equals(new int[] {1, 0, 1}, pc[6].fastRotation().fastRotation().getSkirt()));
		assertEquals(3, pc[3].fastRotation().getHeight());
		assertEquals(3, pc[3].fastRotation().fastRotation().getWidth());
	}
	public void testSquareRotations(){
		assertTrue(sq1.equals(sq2));
		assertEquals(2, sq2.getHeight());
		assertEquals(2, sq1.getWidth());
		assertTrue(Arrays.equals(new int[] {0, 0}, sq1.getSkirt()));
	}
	public void testStickRotations(){
		assertTrue(stick1.equals(stick3));
		assertTrue(stick2.equals(stick4));
		assertEquals(1, stick1.getWidth());
		assertEquals(1, stick2.getHeight());
		assertEquals(4, stick3.getHeight());
		assertEquals(4, stick4.getWidth());
		assertTrue(Arrays.equals(new int[] {0}, stick3.getSkirt()));
		assertTrue(Arrays.equals(new int[] {0, 0, 0, 0}, stick2.getSkirt()));
	}
	public void testEqualsBasic(){
		assertTrue(Lvar1.equals(Lvar2));
		assertTrue(Lvar1.equals(Lvar3));
		assertTrue(Lvar1.equals(Lvar4));
		assertTrue(Lvar1.equals(Lvar5));
		assertFalse(Lvar1.equals(Lvar6));
		assertFalse(Lvar3.equals(pyr1));
		assertFalse(Lvar7.equals(st1));
	}
	public void testSampleSize() {
		// Check size of pyr piece
		assertEquals(3, pyr1.getWidth());
		assertEquals(2, pyr1.getHeight());
		
		// Now try after rotation
		// Effectively we're testing size and rotation code here
		assertEquals(2, pyr2.getWidth());
		assertEquals(3, pyr2.getHeight());
		
		// Now try with some other piece, made a different way
		Piece l = new Piece(Piece.STICK_STR);
		assertEquals(1, l.getWidth());
		assertEquals(4, l.getHeight());
	}
	
	
	// Test the skirt returned by a few pieces
	public void testSampleSkirt() {
		// Note must use assertTrue(Arrays.equals(... as plain .equals does not work
		// right for arrays.
		assertTrue(Arrays.equals(new int[] {0, 0, 0}, pyr1.getSkirt()));
		assertTrue(Arrays.equals(new int[] {1, 0, 1}, pyr3.getSkirt()));
		
		assertTrue(Arrays.equals(new int[] {0, 0, 1}, s.getSkirt()));
		assertTrue(Arrays.equals(new int[] {1, 0}, sRotated.getSkirt()));
	}
	
	
}
