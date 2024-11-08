
/*
 * File: ProgramHierarchy.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * ---------------------------
 * This file is the starter file for the ProgramHierarchy problem.
 */

import acm.graphics.*;
import acm.program.*;
import java.awt.*;

public class ProgramHierarchy extends GraphicsProgram {

	private static final int BOX_WIDTH = 200;
	private static final int BOX_HEIGHT = 50;
	private static final int OFFSET = BOX_HEIGHT / 2;
	private static final int BOXES_Y = 200;

	private static final int LINE_START_Y = BOXES_Y;
	private static final int LINE_END_Y = BOXES_Y - BOX_HEIGHT;

	private static final int MAIN_BOX_Y = LINE_END_Y - BOX_HEIGHT;

	public void run() {
		int MAIN_BOX_X = (getWidth() - BOX_WIDTH) / 2;
		
//drawing upper box.

		drawBox(MAIN_BOX_X, MAIN_BOX_Y);
		textProgram();

//drawing connecting lines.

		draw3Line();

//drawing down boxes.		

		draw3Box();
		textGraphics();
		textConsole();
		textDialog();
	}

//drawing 3 boxes.

	private void draw3Box() {
		int BOXES_X = (getWidth() - 3 * BOX_WIDTH - BOX_HEIGHT) / 2;

		for (int i = 0; i < 3; i++) {
			drawBox(BOXES_X, BOXES_Y);
			BOXES_X += BOX_WIDTH + OFFSET;
		}
	}

//method to draw 3 equal box, needs x and y coordinate for position.

	private void drawBox(int x, int y) {
		GRect box = new GRect(BOX_WIDTH, BOX_HEIGHT);
		add(box, x, y);
	}

//draws 3 lines to connect boxes.

	private void draw3Line() {
		int LINE_START_X = getWidth() / 2 - BOX_WIDTH - OFFSET;

		for (int i = 0; i < 3; i++) {
			drawLine(LINE_START_X);
			LINE_START_X += BOX_WIDTH + OFFSET;
		}
	}

//method to draw lines, need starting x coordinate.	

	private void drawLine(int x) {
		GLine line = new GLine(x, LINE_START_Y, getWidth() / 2, LINE_END_Y);
		add(line);
	}

//text for main box.

	private void textProgram() {
		GLabel program = new GLabel("Program");
		add(program, getWidth() / 2 - program.getWidth() / 2,
				MAIN_BOX_Y + BOX_HEIGHT / 2 + program.getHeight() / 2 - program.getDescent());
	}

//texts for 3 boxes.

	private void textGraphics() {
		GLabel graphics = new GLabel("GraphicsProgram");
		add(graphics, getWidth() / 2 - BOX_WIDTH - OFFSET - graphics.getWidth() / 2,
				BOXES_Y + BOX_HEIGHT / 2 + graphics.getHeight() / 2 - graphics.getDescent());
	}

	private void textConsole() {
		GLabel console = new GLabel("ConsoleProgram");
		add(console, getWidth() / 2 - console.getWidth() / 2,
				BOXES_Y + BOX_HEIGHT / 2 + console.getHeight() / 2 - console.getDescent());
	}

	private void textDialog() {
		GLabel dialog = new GLabel("DialogProgram");
		add(dialog, getWidth() / 2 + BOX_WIDTH + OFFSET - dialog.getWidth() / 2,
				BOXES_Y + BOX_HEIGHT / 2 + dialog.getHeight() / 2 - dialog.getDescent());
	}
}
