/*
 * File: CollectNewspaperKarel.java
 * --------------------------------
 * At present, the CollectNewspaperKarel subclass does nothing.
 * Your job in the assignment is to add the necessary code to
 * instruct Karel to walk to the door of its house, pick up the
 * newspaper (represented by a beeper, of course), and then return
 * to its initial position in the upper left corner of the house.
 */

import stanford.karel.*;

public class CollectNewspaperKarel extends SuperKarel {
	public void run() {
		CollectNewspaper();
	}
	
//Karel comes out of maze, picks beeper and returns to start.
	
	private void CollectNewspaper() {
		GoToNewspaper();
		pickBeeper();
		GotoStart();
	}
	
//Karel walks the way to newspaper
	
	private void GoToNewspaper() {
		turnRight();
        move();
        turnLeft();
        MoveByThree();
	}

//Karel returns to start position
	
	private void GotoStart() {
        turnAround();
        MoveByThree();
        turnRight();
        move();
        turnRight();
	}
	
//Karel moves by 3
	
	private void MoveByThree() {
        move();
        move();
        move();
    }
}