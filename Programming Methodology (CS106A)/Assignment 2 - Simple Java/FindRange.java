
/*
 * File: FindRange.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * --------------------
 * This file is the starter file for the FindRange problem.
 */

import acm.program.*;

public class FindRange extends ConsoleProgram {

	private static final int specialSymbol = 0;

	public void run() {
		println("This program finds the largest and smallest numbers.");
		findRange();
	}

//with this method we firstly we compare 2 ints x and a, then keep max amd min numbers and continue comparing in while
	private void findRange() {
		int x = readInt("? ");
		int max = x;
		int min = x;
		if (x == specialSymbol) {
			println("You have entered special symbol. Use it only if u want to stop entering numbers.");
		} else {
			while (true) {
				int a = readInt("? ");
// if int will be equal to special symbol program should stop.
				if (a == specialSymbol) {
					finalText(min, max);
					break;
				} else {
					max = Math.max(a, max);
					min = Math.min(a, min);
				}
			}
		}
	}

//method to write final text.
	private void finalText(int smallest, int largest) {
		println("smallest: " + smallest);
		println("largest: " + largest);
	}
}
