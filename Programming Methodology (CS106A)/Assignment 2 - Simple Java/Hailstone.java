
/*
 * File: Hailstone.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * --------------------
 * This file is the starter file for the Hailstone problem.
 */

import acm.program.*;

public class Hailstone extends ConsoleProgram {

	public void run() {
		int n = readInt("Enter a number: ");
		roadto1(n);
	}

//this method checks n and changes it until it reaches 1.

	private void roadto1(int n) {
		int i = 0;
		while (true) {
			if (n % 2 == 0) {
				println(n + " is even, so I take half: " + n / 2);
				n = n / 2;
			} else {
				println(n + " is odd, so I make 3n + 1: " + (3 * n + 1));
				n = 3 * n + 1;
			}
			i++;
			if (n == 1) {
				println("The process took " + 12 + " to reach 1");
				break;
			}
		}
	}
}
