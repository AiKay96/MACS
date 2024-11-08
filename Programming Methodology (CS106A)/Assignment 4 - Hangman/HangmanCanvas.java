
/*
 * File: HangmanCanvas.java
 * ------------------------
 * This file keeps track of the Hangman display.
 */

import acm.graphics.*;

public class HangmanCanvas extends GCanvas {
	private String s = "";

	/** Resets the display so that only the scaffold appears */
	public void reset() {
		removeAll();
		s = "";
	}

	/**
	 * Updates the word on the screen to correspond to the current state of the
	 * game. The argument string shows what letters have been guessed so far;
	 * unguessed letters are indicated by hyphens.
	 */
	public void displayWord(String hidden) {
		double x = getWidth() / 2 - BEAM_LENGTH;
		double y = getHeight() / 8 + SCAFFOLD_HEIGHT;
		if (getElementAt(x, y) != null) {
			remove(getElementAt(x, y));
		}
		GLabel txt = new GLabel(hidden);
		txt.setFont("Helvetica-25");
		add(txt, x, y);
	}

	/**
	 * Updates the display to correspond to an incorrect guess by the user. Calling
	 * this method causes the next body part to appear on the scaffold and adds the
	 * letter to the list of incorrect guesses that appears at the bottom of the
	 * window.
	 */
	public void noteIncorrectGuess(char letter) {
		s += letter;
		double x = getWidth() / 2 - BEAM_LENGTH;
		double y = (getHeight() * 61) / 64;
		GLabel txt = new GLabel(s);
		txt.setFont("Helvetica-18");
		add(txt, x, y);
	}

	/* Constants for the simple version of the picture (in pixels) */
	private static final int SCAFFOLD_HEIGHT = 360;
	private static final int BEAM_LENGTH = 144;
	private static final int ROPE_LENGTH = 18;
	private static final int HEAD_RADIUS = 36;
	private static final int BODY_LENGTH = 144;
	private static final int ARM_OFFSET_FROM_HEAD = 28;
	private static final int UPPER_ARM_LENGTH = 72;
	private static final int LOWER_ARM_LENGTH = 44;
	private static final int HIP_WIDTH = 36;
	private static final int LEG_LENGTH = 108;
	private static final int FOOT_LENGTH = 28;

	/** Draws only tree and rope */
	public void startingCanvas() {
		double Sx = getWidth() / 2 - BEAM_LENGTH;
		double Sy = getHeight() / 16;
		GLine scaffold = new GLine(Sx, Sy, Sx, Sy + SCAFFOLD_HEIGHT);
		add(scaffold);
		double Bx = Sx;
		double By = Sy;
		GLine beam = new GLine(Bx, By, Bx + BEAM_LENGTH, By);
		add(beam);
		double Rx = getWidth() / 2;
		double Ry = Sy;
		GLine rope = new GLine(Rx, Ry, Rx, Ry + ROPE_LENGTH);
		add(rope);
	}

	/** Draws man's head */
	public void drawHead() {
		double x = getWidth() / 2 - HEAD_RADIUS;
		double y = getHeight() / 16 + ROPE_LENGTH;
		GOval head = new GOval(2 * HEAD_RADIUS, 2 * HEAD_RADIUS);
		add(head, x, y);
	}

	/** Draws man's body */
	public void drawBody() {
		double x = getWidth() / 2;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS;
		GLine body = new GLine(x, y, x, y + BODY_LENGTH);
		add(body);
	}

	/** Draws man's left arm */
	public void drawLeftArm() {
		double x = getWidth() / 2 - UPPER_ARM_LENGTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + ARM_OFFSET_FROM_HEAD;
		GLine upperArm = new GLine(x, y, x + UPPER_ARM_LENGTH, y);
		GLine lowerArm = new GLine(x, y, x, y + LOWER_ARM_LENGTH);
		add(upperArm);
		add(lowerArm);
	}

	/** Draws man's right arm */
	public void drawRightArm() {
		double x = getWidth() / 2 + UPPER_ARM_LENGTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + ARM_OFFSET_FROM_HEAD;
		GLine upperArm = new GLine(x, y, x - UPPER_ARM_LENGTH, y);
		GLine lowerArm = new GLine(x, y, x, y + LOWER_ARM_LENGTH);
		add(upperArm);
		add(lowerArm);
	}

	/** Draws man's left leg */
	public void drawLeftLeg() {
		double x = getWidth() / 2 - HIP_WIDTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + BODY_LENGTH;
		GLine hip = new GLine(x, y, x + HIP_WIDTH, y);
		GLine leg = new GLine(x, y, x, y + LEG_LENGTH);
		add(hip);
		add(leg);
	}

	/** Draws man's right leg */
	public void drawRightLeg() {
		double x = getWidth() / 2 + HIP_WIDTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + BODY_LENGTH;
		GLine hip = new GLine(x, y, x - HIP_WIDTH, y);
		GLine leg = new GLine(x, y, x, y + LEG_LENGTH);
		add(hip);
		add(leg);
	}

	/** Draws man's left foot */
	public void drawLeftFoot() {
		double x = getWidth() / 2 - HIP_WIDTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + BODY_LENGTH + LEG_LENGTH;
		GLine foot = new GLine(x, y, x - FOOT_LENGTH, y);
		add(foot);
	}

	/** Draws man's right foot */
	public void drawRightFoot() {
		double x = getWidth() / 2 + HIP_WIDTH;
		double y = getHeight() / 16 + ROPE_LENGTH + 2 * HEAD_RADIUS + BODY_LENGTH + LEG_LENGTH;
		GLine foot = new GLine(x, y, x + FOOT_LENGTH, y);
		add(foot);
	}
}
