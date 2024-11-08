
/*
 * File: PythagoreanTheorem.java
 * Name: Anna Kordzadze
 * Section Leader: Nika Glunchadze
 * -----------------------------
 * This file is the starter file for the PythagoreanTheorem problem.
 */

import acm.program.*;

public class PythagoreanTheorem extends ConsoleProgram {
	public void run() {
		println("Enter values to compute Pythagorean Theorem");
		int a = readInt("a: ");
		int b = readInt("b: ");
		println("c = " + Pythagore(a, b));
	}

//method for Pythagorean theorem.
	private double Pythagore(int a, int b) {
		int c = a * a + b * b;
		double result = Math.sqrt(c);
		return result;
	}
}
