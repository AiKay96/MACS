
// Test cases for CharGrid -- a few basic tests are provided.

import junit.framework.TestCase;

public class CharGridTest extends TestCase {
	
	public void testCharArea1() {
		char[][] grid = new char[][] {
				{'a', 'y', ' '},
				{'x', 'a', 'z'},
			};
		
		
		CharGrid cg = new CharGrid(grid);
				
		assertEquals(4, cg.charArea('a'));
		assertEquals(1, cg.charArea('z'));
		assertEquals(0, cg.charArea('b'));
	}
	
	
	public void testCharArea2() {
		char[][] grid = new char[][] {
				{'c', 'a', ' '},
				{'b', ' ', 'b'},
				{' ', ' ', 'a'}
			};
		
		CharGrid cg = new CharGrid(grid);
		
		assertEquals(6, cg.charArea('a'));
		assertEquals(3, cg.charArea('b'));
		assertEquals(1, cg.charArea('c'));
	}
	public void testCharArea3() {
		//full rectange test
		char[][] grid = new char[][] {
				{'a', ' ', 'c'},
				{' ', ' ', ' '},
				{'c', ' ', 'a'}
		};

		CharGrid cg = new CharGrid(grid);

		assertEquals(9, cg.charArea('a'));
		assertEquals(9, cg.charArea('c'));
		assertEquals(0, cg.charArea('b'));
	}
	public void testCharArea4() {
		//normal cases
		char[][] grid = new char[][] {
				{'c', 'a', ' ', 'a', 'c'},
				{'b', ' ', ' ', 'z' , ' '},
				{'b', 'a', 'a', ' ' , 'z'}
		};

		CharGrid cg = new CharGrid(grid);

		assertEquals(9, cg.charArea('a'));
		assertEquals(5, cg.charArea('c'));
		assertEquals(2, cg.charArea('b'));
		assertEquals(4, cg.charArea('z'));
	}
	public void testCharArea5() {
		//empty
		char[][] grid = new char[][] {
				{' ', ' '},
				{' ', ' '}
		};

		CharGrid cg = new CharGrid(grid);

		assertEquals(0, cg.charArea('a'));
		assertEquals(0, cg.charArea('b'));
		assertEquals(0, cg.charArea('c'));
	}

	public void testPlusCount1() {
		char[][] grid = new char[][] {
				{' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ',},
				{' ', ' ', 'x', ' ', ' ', ' ', ' ', 'x', ' ',},
				{' ', 'x', 'x', 'x', ' ', ' ', 'x', 'x', 'x',},
				{' ', ' ', 'x', ' ', ' ', 'y', ' ', 'x', ' ',},
				{' ', ' ', 'p', ' ', 'y', 'y', 'y', ' ', ' ',},
				{'z', 'p', 'p', 'p', 'z', 'y', 'z', 'z', 'z',},
				{' ', ' ', 'p', 'x', ' ', 'y', ' ', ' ', ' ',}
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(3, cg.countPlus());
	}
	public void testPlusCount2() {
		char[][] grid = new char[][] {
				{' ', ' ', 'x', ' ', ' ', 'a', ' ', ' ', ' ',},
				{' ', ' ', 'x', ' ', ' ', ' ', ' ', 'x', ' ',},
				{' ', 'x', 'x', 'x', ' ', ' ', 'x', 'x', 'x',},
				{' ', ' ', 'x', ' ', ' ', 'y', ' ', 'x', ' ',},
				{' ', ' ', 'p', ' ', 'y', 'y', 'y', ' ', ' ',},
				{'z', 'p', 'p', 'p', 'z', 'y', 'z', 'z', 'z',},
				{' ', ' ', 'p', 'x', ' ', ' ', ' ', ' ', ' ',}
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(3, cg.countPlus());
	}
	public void testPlusCount3() {
		char[][] grid = new char[][] {
				{' ', ' ', ' ', ' ', 'a', 'a', 'a', ' ', ' ',},
				{' ', ' ', 'x', ' ', ' ', 'a', ' ', 'x', ' ',},
				{' ', 'x', 'x', 'x', ' ', ' ', 'x', 'x', 'x',},
				{' ', ' ', 'x', ' ', ' ', 'y', ' ', 'x', ' ',},
				{' ', ' ', 'p', ' ', 'y', 'y', 'y', 'z', ' ',},
				{'z', 'p', 'p', 'p', 'z', 'y', 'z', 'z', 'z',},
				{' ', ' ', 'p', 'x', ' ', 'z', ' ', ' ', ' ',}
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(4, cg.countPlus());
	}
	public void testPlusCount4() {
		char[][] grid = new char[][] {
				{' ', ' ', ' ', ' ', ' ', 'a', ' ', ' ', ' ',},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ',},
				{' ', ' ', ' ', 'x', ' ', ' ', 'x', ' ', 'x',},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', 'x', ' ',},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', 'z',},
				{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',}
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(0, cg.countPlus());
	}
	public void testPlusCount5() {
		char[][] grid = new char[][] {
				{' '}
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(0, cg.countPlus());
	}
	public void testPlusCount6() {
		char[][] grid = new char[][] {
				{'x', 'x', 'x'},
				{'x', 'x', 'x'},
				{'x', 'x', 'x'},
		};

		CharGrid cg = new CharGrid(grid);
		assertEquals(1, cg.countPlus());
	}
	
	
	
}
