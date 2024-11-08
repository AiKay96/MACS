
/*
 * File: Yahtzee.java
 * ------------------
 * This program will eventually play the Yahtzee game.
 */

import java.util.ArrayList;
import java.util.Arrays;

import acm.io.*;
import acm.program.*;
import acm.util.*;

public class Yahtzee extends GraphicsProgram implements YahtzeeConstants {

	public static void main(String[] args) {
		new Yahtzee().start(args);
	}

	public void run() {
		IODialog dialog = getDialog();
		nPlayers = dialog.readInt("Enter number of players");
		playerNames = new String[nPlayers];
		for (int i = 1; i <= nPlayers; i++) {
			playerNames[i - 1] = dialog.readLine("Enter name for player " + i);
		}
		display = new YahtzeeDisplay(getGCanvas(), playerNames);
		scoreTable = new int[N_CATEGORIES][nPlayers];
		for (int[] i : scoreTable) {
			Arrays.fill(i, -1);
		}
		for (int i = 0; i < scoreTable.length; i++) {
			for (int j = 0; j < scoreTable[i].length; j++) {
				if (i == UPPER_SCORE - 1 || i == UPPER_BONUS - 1 || i == LOWER_SCORE - 1 || i == TOTAL - 1) {
					scoreTable[i][j] = 0;
				}
			}
		}
		playGame();
	}

	private void playGame() {
		//game process.
		for (int i = 0; i < N_SCORING_CATEGORIES; i++) {
			for (int j = 0; j < nPlayers; j++) {
				display.printMessage(playerNames[j] + "'s turn! Click button to roll the dice.");
				display.waitForPlayerToClickRoll(j + 1);
				rollStartDices();
				for (int k = 0; k < 2; k++) {
					display.printMessage("Select the dice you wish to re-roll and click \"Roll Again\".");
					rollAgain();
				}
				display.printMessage("Select a category for this roll.");
				selectCategory(j);
			}
		}
		//summing scores.
		for (int i = 0; i < nPlayers; i++) {
			int upperScore = 0;
			int lowerScore = 0;
			int bonus = 0;
			for (int j = 0; j < SIXES; j++) {
				upperScore += scoreTable[j][i];
				display.updateScorecard(UPPER_SCORE, i + 1, upperScore);
				if (upperScore >= 63) {
					bonus = 35;
				} else {
					bonus = 0;
				}
				display.updateScorecard(UPPER_BONUS, i + 1, bonus);
			}
			for (int j = THREE_OF_A_KIND - 1; j < CHANCE; j++) {
				lowerScore += scoreTable[j][i];
				display.updateScorecard(LOWER_SCORE, i + 1, lowerScore);
			}
			display.updateScorecard(TOTAL, i + 1, scoreTable[TOTAL - 1][i] + bonus);
			scoreTable[UPPER_SCORE - 1][i] = upperScore;
			scoreTable[UPPER_BONUS - 1][i] = bonus;
			scoreTable[LOWER_SCORE - 1][i] = lowerScore;
		}
		//choosing winner.
		int winnerScore = 0;
		int winner = 0;
		for (int i = 0; i < nPlayers; i++) {
			if (winnerScore < scoreTable[TOTAL - 1][i]) {
				winnerScore = scoreTable[TOTAL - 1][i];
				winner = i;
			}
		}
		display.printMessage("Congratulations, " + playerNames[winner] + ", you're the winner with a total score of "
				+ winnerScore + "!");
	}

	/**
	 * method that make player able to select category, which will be checked after
	 * that.
	 */
	private void selectCategory(int playerN) {
		int category = 0;
		while (true) {
			category = display.waitForPlayerToSelectCategory();
			if (scoreTable[category - 1][playerN] == -1) {
				break;
			}
		}
		int score = score(category);
		scoreTable[category - 1][playerN] = score;
		scoreTable[TOTAL - 1][playerN] += score;
		display.updateScorecard(TOTAL, playerN + 1, scoreTable[TOTAL - 1][playerN]);
		display.updateScorecard(category, playerN + 1, score);
	}

	/** method that checks every case and returns score. */
	private int score(int category) {
		int score = 0;
		Arrays.sort(rolledDices);
		if (category <= SIXES) {
			score = checkSix(category);
		} else if (category <= FOUR_OF_A_KIND || category == YAHTZEE) {
			score = checkKind(category);
		} else if (category == FULL_HOUSE) {
			score = checkHouse(category);
		} else if (category == CHANCE) {
			score = chanceScore();
		} else if (category >= SMALL_STRAIGHT) {
			score = checkStraight(category);
		}
		return score;
	}

	/** method that sums all dices. returns score. */
	private int chanceScore() {
		int sum = 0;
		for (int i = 0; i < N_DICE; i++) {
			sum += rolledDices[i];
		}
		return sum;
	}

	/**
	 * method that checks how many numbers are straight, then which case it is,
	 * returns score.
	 */
	private int checkStraight(int category) {
		int sum = 0;
		int n = 0;
		ArrayList<Integer> dices = new ArrayList<>();
		for (int i : rolledDices) {
			if (dices.indexOf(i) == -1) {
				dices.add(i);
			}
		}
		for (int i = 0; i < dices.size() - 1; i++) {
			if (dices.get(i) + 1 == dices.get(i + 1)) {
				n++;
			}
		}
		if (n >= 3) {
			sum = 30;
		}
		if (n == 4 && category == LARGE_STRAIGHT) {
			sum = 40;
		}
		return sum;
	}

	/** uses fullHouse boolean to check full house case. return score. */
	private int checkHouse(int category) {
		int sum = 0;
		boolean isFullHouse = fullHouse(2) || fullHouse(3);
		if (isFullHouse) {
			sum = 25;
		}
		return sum;
	}

	/**
	 * method that will be checked from 2 and 3. returns answer for isFullHouse
	 * boolean.
	 */
	private boolean fullHouse(int n) {
		boolean x = true;
		// checks if it isn't yahtzee
		if (rolledDices[n - 1] == rolledDices[n]) {
			x = false;
		}
		// checks if dices are same before n.
		for (int i = 0; i < n - 1; i++) {
			if (rolledDices[i] != rolledDices[i + 1]) {
				x = false;
			}
		}
		// checks if dices are same after n.
		for (int i = n; i < N_DICE - 1; i++) {
			if (rolledDices[i] != rolledDices[i + 1]) {
				x = false;
			}
		}
		return x;
	}

	/**
	 * method to check same dices, which are in number of a kind and yahtzee cases.
	 * returns score
	 */
	private int checkKind(int category) {
		int sum = 0;
		int n = 0;
		for (int i = 0; i < N_DICE - 1; i++) {
			if (rolledDices[i] == rolledDices[i + 1]) {
				n++;
			}
		}
		if (n == 4 && category == YAHTZEE) {
			sum = 50;
		} else if ((n == 4 && category == FOUR_OF_A_KIND) || (n == 4 && category == THREE_OF_A_KIND)
				|| (n == 3 && category == FOUR_OF_A_KIND) || (n == 3 && category == THREE_OF_A_KIND)
				|| (n == 2 && category == THREE_OF_A_KIND)) {
			for (int i = 0; i < N_DICE; i++) {
				sum += rolledDices[i];
			}
		}
		return sum;
	}

	/** method to check first six cases. returns score. */
	private int checkSix(int category) {
		int sum = 0;
		for (int i = 0; i < N_DICE; i++) {
			if (rolledDices[i] == category) {
				sum += category;
			}
		}
		return sum;
	}

	/**
	 * if player will choose 1 or 2 dice to reroll, this method rerolls only them
	 * and displays result.
	 */
	private void rollAgain() {
		display.waitForPlayerToSelectDice();
		for (int i = 0; i < N_DICE; i++) {
			if (display.isDieSelected(i)) {
				rolledDices[i] = rollOneDice();
			}
		}
		display.displayDice(rolledDices);
	}

	/** rolls starting 5 dices and displays it. */
	private void rollStartDices() {
		for (int i = 0; i < N_DICE; i++) {
			rolledDices[i] = rollOneDice();
		}
		display.displayDice(rolledDices);
	}

	/** rolls one dice, chooses random number from 1 to 6. */
	private int rollOneDice() {
		return rgen.nextInt(1, 6);
	}

	/* Private instance variables */
	private int[][] scoreTable;
	private int[] rolledDices = new int[N_DICE];
	private int nPlayers;
	private String[] playerNames;
	private YahtzeeDisplay display;
	private RandomGenerator rgen = new RandomGenerator();

}
