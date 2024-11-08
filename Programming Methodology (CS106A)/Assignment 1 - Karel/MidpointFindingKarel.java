/*
 * File: MidpointFindingKarel.java
 * -------------------------------
 * When you finish writing it, the MidpointFindingKarel class should
 * leave a beeper on the corner closest to the center of 1st Street
 * (or either of the two central corners if 1st Street has an even
 * number of corners).  Karel can put down additional beepers as it
 * looks for the midpoint, but must pick them up again before it
 * stops.  The world may be of any size, but you are allowed to
 * assume that it is at least as tall as it is wide.
 */

import stanford.karel.*;

public class MidpointFindingKarel extends SuperKarel {

	public void run() {
		Position();
		FindCenter();
		GoDown();
		putBeeper();
	}
	
//Karel should face south to start code, to always check walls properly (in center while loop)
	private void Position() {
		turnLeft();
	}
	
//Karel goes on way to midpoint on parallel
	
	private void FindCenter() {
		while (frontIsClear()) {
			turnRight();
			move();
			turnLeft();
			if (frontIsClear()) {
				moveByTwo();
			}
		}
	}
	
//Karel moves by two
	
	private void moveByTwo() {
		move();
		if (frontIsClear()) {
			move();
		}
	}
	
//Karel goes down
	
	private void GoDown() {
		turnAround();
		while(frontIsClear()) {
			move();
		}
	}

}
