
/*
 * File: Target.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * -----------------
 * This file is the starter file for the Target problem.
 */

import acm.graphics.*;
import acm.program.*;
import java.awt.*;

public class Target extends GraphicsProgram {
	/** Number of cyrcles in target */

	private static final int CYRCLE_N = 3;

	/** Cyrcle radiuses in pixels */

	private int Radius = 72;

	/** Difference in cyrcle radiuses in pixels */

	private static final int r = 25;

	public void run() {
		drawTarget();
	}

	// Method to make cyrcles. It will draw 3 cyrcles and reduce radius adn change
	// color for each time.

	private void drawTarget() {
		for (int i = 0; i < CYRCLE_N; i++) {
			drawCyrcle(Radius, i);
			Radius -= r;
		}
	}

	// Method to make cyrcle. Parameters are cyrcle radius and cyrcle number. if i
	// is odd cyrcle is white, else if cyrcle is even is red.

	private void drawCyrcle(int R, int i) {
		GOval cyrcle = new GOval(2 * R, 2 * R);
		if (i % 2 == 0) {
			cyrcle.setColor(Color.RED);
			cyrcle.setFilled(true);
			cyrcle.setFillColor(Color.RED);
		} else {
			cyrcle.setColor(Color.WHITE);
			cyrcle.setFilled(true);
			cyrcle.setFillColor(Color.WHITE);
		}
		add(cyrcle, getWidth() / 2 - R, getHeight() / 2 - R);
	}
}
