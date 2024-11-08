/*
 * File: CheckerboardKarel.java
 * ----------------------------
 * When you finish writing it, the CheckerboardKarel class should draw
 * a checkerboard using beepers, as described in Assignment 1.  You
 * should make sure that your program works for all of the sample
 * worlds supplied in the starter folder.
 */

import stanford.karel.*;

public class CheckerboardKarel extends SuperKarel {

	public void run() {
		DoCheckerBoard();
	}
	
//Karel makes checker board
	private void DoCheckerBoard() {
		if (frontIsClear()) {
			FillLine();
		} else {
			FillVertical();
		}
	}
	
//Karel fills 1 vertical line when world is 1 x n
	
	private void FillVertical() {
		turnLeft();
		FillFirstLine();
	}
	
//Karel fills whole board with 2 types of filling lines
	
	private void FillLine() {
		while (frontIsClear()) {
			FillFirstLine();
			ReturnToStart();
			if (rightIsClear()) {
				NextLine();
				FillSecondLine();
				ReturnToStart();
				NextLine();
			}
		}
		
	}

//Karel fills one line with beepers from start
	
	private void FillFirstLine() {
		putBeeper();
		while (frontIsClear()) {
			MoveByTwoAndPutBeeper();
		}
	}
	
//Karel fills one line with beepers from second cell
	
	private void FillSecondLine() {
		if (frontIsClear()) {
			move();
			FillFirstLine();
		}
	}

//Karel moves by two and puts 1 beeper
	
	private void MoveByTwoAndPutBeeper() {
		move();
		if (frontIsClear()) {
			move();
			putBeeper();
		}
	}

//Karel returns to start position, but it will face west at the end
	
	private void ReturnToStart() {
		turnAround();
		while (frontIsClear()) {
			move();
		}
	}
	
//Karel goes up on next line
	
	private void NextLine() {
		turnRight();
		if (frontIsClear()) {
			move();
			turnRight();
		}
	}
}
