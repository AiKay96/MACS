
/*
 * File: HangmanLexicon.java
 * -------------------------
 * This file contains a stub implementation of the HangmanLexicon
 * class that you will reimplement for Part III of the assignment.
 */

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import acm.util.*;

public class HangmanLexicon {

	private ArrayList<String> words = new ArrayList<String>();

	/** This is the HangmanLexicon constructor. */
	public HangmanLexicon() {
		try {
			BufferedReader rd = new BufferedReader(new FileReader("HangmanLexicon.txt"));
			String line = "";
			while (true) {
				line = rd.readLine();
				if (line == null) {
					break;
				}
				/** if line isn't empty it will add to array. */
				if (line.equals("") == false) {
					words.add(line);
				}
			}
			rd.close();
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	/** Returns the number of words in the lexicon. */
	public int getWordCount() {
		return words.size();
	}

	/** Returns the word at the specified index. */
	public String getWord(int index) {
		return words.get(index);
	}
}
