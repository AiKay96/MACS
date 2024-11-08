/*
 * File: StoneMasonKarel.java
 * --------------------------
 * The StoneMasonKarel subclass as it appears here does nothing.
 * When you finish writing it, it should solve the "repair the quad"
 * problem from Assignment 1.  In addition to editing the program,
 * you should be sure to edit this comment so that it no longer
 * indicates that the program does nothing.
 */

import stanford.karel.*;

public class StoneMasonKarel extends SuperKarel {
	public void run() {
		Build();
	}
	
//Karel moves by four to fix next building
	
	private void NextBuilding() {
        move();
        move();
        move();
        move();
    }
//Karel builds Masons
	
	private void Build() {
		BuildOneMason();
		while (frontIsClear()) {
			NextBuilding();
			BuildOneMason();
		}
    }

//Karel builds stone masons, It should look up (turnLeft), then build mason and gets to starting position.
	
	private void BuildOneMason() {
		turnLeft();
		CheckBeeper();
		while (frontIsClear()) {
			move();
			CheckBeeper();	
		}
		goDown();
	}
	
//Karel checks beepers, if no beepers present it puts them
	
	private void CheckBeeper() {
		if (noBeepersPresent()) {
			 putBeeper();
		}
	}

//Karel goes down
	
	private void goDown() {
		turnAround();
		while (frontIsClear()) {
			move();
		}
		turnLeft();
	}
}
