
/*
 * File: Hangman.java
 * ------------------
 * This program will eventually play the Hangman game from
 * Assignment #4.
 */

import acm.graphics.*;
import acm.program.*;
import acm.util.*;

import java.awt.*;

public class Hangman extends ConsoleProgram {

	private RandomGenerator rgen = RandomGenerator.getInstance();
	private int lifes = 8;

	private HangmanCanvas canvas;
	private HangmanLexicon lexicon;

	public void init() {
		canvas = new HangmanCanvas();
		add(canvas);
	}

	public void run() {
		lexicon = new HangmanLexicon();
		println("Welcome to Hangman!");
		while (true) {
			String word = random();
			String hidden = hideWord(word);
			process(word, hidden);
			int answer = readInt("Enter 1 if you want to play again: ");
			if (answer == 1) {
				canvas.reset();
				lifes = 8;
			}
			if (answer != 1) {
				break;
			}
		}
	}

	/** choose random word */
	private String random() {
		int n = lexicon.getWordCount();
		println(n);
		int cases = rgen.nextInt(0, n - 1);
		println(cases);
		String word = lexicon.getWord(cases);
		return word;
	}

	/** method to play while you will win or lose. */
	private void process(String word, String hidden) {
		canvas.startingCanvas();
		while (true) {
			canvas.displayWord(hidden);
			println("The word now looks like this: " + hidden);
			println("You have " + lifes + " guesses left.");
			String s = readLine("Your guess: ");
			char guess = readChar(s);
			hidden = check(word, hidden, guess);
			if (lifes == 7)
				canvas.drawHead();
			if (lifes == 6)
				canvas.drawBody();
			if (lifes == 5)
				canvas.drawLeftArm();
			if (lifes == 4)
				canvas.drawRightArm();
			if (lifes == 3)
				canvas.drawLeftLeg();
			if (lifes == 2)
				canvas.drawRightLeg();
			if (lifes == 1)
				canvas.drawLeftFoot();
			if (lifes == 0) {
				canvas.drawRightFoot();
				println("You're complerely hung.");
				println("The word was: " + word + ".");
				println("You lose.");
				break;
			}
			if (hidden.equals(word)) {
				canvas.displayWord(hidden);
				println("You guessed the word: " + word + ".");
				println("You win.");
				break;
			}
		}
	}

	/**
	 * checks if character is in string and shows it, if it is or if it isn't
	 * reduces life.
	 */
	private String check(String word, String hidden, char ch) {
		String st = word;
		String result = hidden;
		if (st.indexOf(ch) == -1) {
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				lifes--;
				println("There are no " + ch + "'s in the word.");
				canvas.noteIncorrectGuess(ch);
			} else {
				println("Please enter only characters.");
			}
		}
		if (st.indexOf(ch) != -1) {
			if (result.indexOf(ch) != -1) {
				println("You have already entered this character. Try another.");
			}
			if (result.indexOf(ch) == -1) {
				println("That guess is correct.");
			}
			while (st.indexOf(ch) != -1) {
				result = result.substring(0, st.indexOf(ch)) + ch
						+ result.substring(st.indexOf(ch) + 1, hidden.length());
				st = st.substring(0, st.indexOf(ch)) + "0" + st.substring(st.indexOf(ch) + 1, st.length());
			}
		}
		return result;
	}

	/** hides word with "-". */
	private String hideWord(String s) {
		for (int i = 0; i < s.length(); i++) {
			s = s.substring(0, i) + "-" + s.substring(i + 1, s.length());
		}
		return s;
	}

	/** method that changes string to character. */
	private char readChar(String s) {
		if (s.length() == 1) {
			char ch = s.charAt(0);
			if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
				if (ch >= 'a' && ch <= 'z') {
					ch = Character.toUpperCase(ch);
				}
				return ch;
			}
		}
		return 0;
	}
}