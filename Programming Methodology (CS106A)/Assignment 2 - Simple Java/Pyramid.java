
/*
 * File: Pyramid.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * ------------------
 * This file is the starter file for the Pyramid problem.
 * It includes definitions of the constants that match the
 * sample run in the assignment, but you should make sure
 * that changing these values causes the generated display
 * to change accordingly.
 */

import acm.graphics.*;
import acm.program.*;
import java.awt.*;

public class Pyramid extends GraphicsProgram {

	/** Width of each brick in pixels */
	private static final int BRICK_WIDTH = 30;

	/** Width of each brick in pixels */
	private static final int BRICK_HEIGHT = 12;

	/** Number of bricks in the base of the pyramid */
	private static final int BRICKS_IN_BASE = 14;

	private int n = BRICKS_IN_BASE;

	public void run() {
		// position coordinates for brick N1. (left one)
		double x = (getWidth() - BRICKS_IN_BASE * BRICK_WIDTH) / 2;
		double y = getHeight() - BRICK_HEIGHT;

		createPyramid(x, y);
	}

	/*
	 * Method to make 1 row with bricks. Parameters are coordinates for position for
	 * each brick. After creating row n(Bricks quantity in base) reduces by 1. So
	 * with 14, 13, ..., 1 bricks program creates pyramid.
	 */

	private void createPyramid(double x, double y) {
		for (int i = 0; i < BRICKS_IN_BASE; i++) {
			createRow(x, y);
			n--;
			x += BRICK_WIDTH / 2;
			y -= BRICK_HEIGHT;
		}
	}

	/*
	 * Method to make 1 row with bricks. Parameters are coordinates for position for
	 * each brick. Only x coordinate changes. Bricks should be next to each other.
	 */

	private void createRow(double x, double y) {
		for (int i = 0; i < n; i++) {
			createBrick(x, y);
			x = x + BRICK_WIDTH;
		}
	}

//Method to make only 1 brick. Parameters are coordinates for position.

	private void createBrick(double x, double y) {
		GRect brick = new GRect(BRICK_WIDTH, BRICK_HEIGHT);
		add(brick, x, y);
	}
}
