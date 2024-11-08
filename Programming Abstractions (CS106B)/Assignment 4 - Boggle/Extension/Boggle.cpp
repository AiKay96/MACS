/*
 * File: Boggle.cpp
 * ----------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the main starter file for Assignment #4, Boggle.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gboggle.h"
#include "grid.h"
#include "gwindow.h"
#include "lexicon.h"
#include "random.h"
#include "simpio.h"
#include "vector.h"
using namespace std;

/* Constants */

const int BOGGLE_WINDOW_WIDTH = 650;
const int BOGGLE_WINDOW_HEIGHT = 350;

int boardN = 4;

int SWAP = 3;
int BLOCK = 3;
int DICTATION = 3;

const string STANDARD_CUBES[16]  = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};
 
const string BIG_BOGGLE_CUBES[25]  = {
    "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
    "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
    "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
    "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
    "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

/* Function prototypes */

void welcome();
void giveInstructions();
void askInstructions();
bool askConfiguration();
void standardConfiguration(Grid<char> &charBoard);
string playerConfiguration();
void configuration(Grid<char> &charBoard);
bool wantPlayAgain();
char randomChar(int &i);
void generateBoardSpot(Grid<char> &charBoard, int &index, char ch);
void generatePlayerBoard(Grid<char> &charBoard, string &chars);
void generateStandardBoard(Grid<char> &charBoard);
void wantBigBoggle();
void zeroMatrix(Grid<int> &usedChars);
void block(Grid<int> &usedChars, int x, int y);
void blockRandomCube(Grid<int> &usedChars, int &a, int &b);
void blockColumn(Grid<int> &usedChars, int c);
void showMassages(Grid<char> &charBoard);
void removeHighlights();
void swap(Grid<char> &charBoard, int x1, int y1, int x2, int y2);
void DFS(Grid<char> &charBoard, Grid<int> usedChars, Lexicon &words, Set<string> usedWords, int x, int y, string word, string &s);
string dictate(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords);
bool isWordOnBoard(Grid<char> &charBoard, Grid<int> usedChars, string word, int index, int x, int y);
void playerTurn(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords, bool &canFindWord);
void computerTurn(Grid<char> &charBoard, Grid<int> usedChars, Lexicon &words, Set<string> &usedWords,  bool &canFindWord);
void giveHelps(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords, bool &canFindWord);

/* Main program */
int main() {
    GWindow gw(BOGGLE_WINDOW_WIDTH, BOGGLE_WINDOW_HEIGHT);
    initGBoggle(gw);

	Lexicon words("EnglishWords.dat");
	Grid<char> charBoard;

	bool wantPlay = true;
	while(wantPlay){
		showMassages(charBoard);
		showHelps(SWAP, BLOCK, DICTATION);
		Grid<int> usedChars(boardN,boardN);
		Set<string> usedWords;
		zeroMatrix(usedChars);
		bool canFindWord = true;
		while(canFindWord){
			int x = 0;
			int y = 0;
			blockRandomCube(usedChars, x, y);
			playerTurn(charBoard, usedChars, words, usedWords, canFindWord);
			if(!canFindWord){
				break;
			}
			showHelps(SWAP, BLOCK, DICTATION);
			blockRandomCube(usedChars, x, y);
			computerTurn(charBoard, usedChars, words, usedWords, canFindWord);
			zeroMatrix(usedChars);
			removeHighlights();
		}
		wantPlay = wantPlayAgain();
		boardN = 4;
		SWAP = 3;
		BLOCK = 3;
		DICTATION = 3;
	}
    return 0;
}
/*
 * Function: dictate
 * --------------------------
 * Return word to dictate user.
 */
string dictate(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords){
	string s = "";
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			DFS(charBoard, usedChars, words, usedWords,i,j, "", s);			
		}
	}
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			isWordOnBoard(charBoard, usedChars, s, 0, i, j);	
		}
	}
	recordWordForPlayer(s, HUMAN);
	usedWords.add(toLowerCase(s));
	return s;
}
/*
 * Function: DFS
 * --------------------------
 * Return the longest word.
 */
void DFS(Grid<char> &charBoard, Grid<int> usedChars, Lexicon &words, Set<string> usedWords, int x, int y, string word, string &s){
	if(words.contains(word) && !usedWords.contains(toLowerCase(word)) && word.length() >= 4){
		usedWords.add(toLowerCase(word));
		if(s.length() < word.length()){
			s = word;
		}
	}
	if(!words.containsPrefix(toLowerCase(word)) || x < 0 || y < 0 || x > boardN - 1 || y > boardN - 1 || usedChars[x][y] > 0){
		return;
	}
	word+= charBoard[x][y];
	usedChars[x][y]++;
	for(int i = x - 1; i <= x+1; i++){
		for(int j = y -1; j <= y+1; j++){
			DFS(charBoard, usedChars, words, usedWords, i, j, word, s);
		}
	}
}
/*
 * Function: swap
 * --------------------------
 * Swap 2 character on the board.
 */
void swap(Grid<char> &charBoard, int x1, int y1, int x2, int y2){
	char temp = charBoard[x1][y1];
	charBoard[x1][y1] = charBoard[x2][y2];
	charBoard[x2][y2] = temp;
	labelCube(x1,y1,charBoard[x1][y1]);
	labelCube(x2,y2,charBoard[x2][y2]);
}
/*
 * Function: blockColumn
 * --------------------------
 * Block 1 column.
 */
void blockColumn(Grid<int> &usedChars, int c){
	zeroMatrix(usedChars);
	for(int i = 0; i < boardN; i++){
		block(usedChars, i, c);
	}
}
/*
 * Function: blockRandomCube
 * --------------------------
 * Block random cube on the board.
 */
void blockRandomCube(Grid<int> &usedChars, int &a, int &b){
	int index = randomInteger(0, boardN*boardN - 1);
	int x = index / boardN;
	int y = index % boardN;
	a = x;
	b = y;
	block(usedChars, x, y);
}

/*
 * Function: block
 * --------------------------
 * Block spot on (x,y).
 */
void block(Grid<int> &usedChars, int x, int y){
	usedChars[x][y]++;
	blockCube(x, y, true);
}

/*
 * Function: wantPlayAgain
 * --------------------------
 * Ask user if he/she wants to play again.
 */
bool wantPlayAgain(){
	string answer = getLine("Would you like to play again? ");
	while(answer != "yes" && answer != "no"){
		cout << "Please answer yes or no." << endl;
		answer = getLine("Would you like to play again? ");
	}
	if(answer == "yes"){
		return true;
	}
	return false;
}
/*
 * Function: zeroMatrix
 * --------------------------
 * Make every spot 0 in grid.
 */
void zeroMatrix(Grid<int> &usedChars){
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			usedChars[i][j] = 0;
		}
	}
}
/*
 * Function: computerTurn
 * --------------------------
 * Search words on the board starting from every spot.
 */
void computerTurn(Grid<char> &charBoard, Grid<int> usedChars, Lexicon &words, Set<string> &usedWords, bool &canFindWord){
	string s = "";
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			DFS(charBoard, usedChars, words, usedWords,i,j, "", s);			
		}
	}
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			isWordOnBoard(charBoard, usedChars, s, 0, i, j);	
		}
	}
	if(s != ""){
		recordWordForPlayer(s, COMPUTER);
		usedWords.add(toLowerCase(s));
	}else{
		cout << "Computer can't find word." << endl;
		cout << "Game has ended." << endl;
		canFindWord = false;
	}
}
/*
 * Function: playerTurn
 * --------------------------
 * Get words from user and show proper massages.
 */
void playerTurn(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords, bool &canFindWord){
	string word = getLine("Enter a word: ");
	while(word != ""){
		if(word.length() < 4){
			cout << "I'm sorry, but we have our standards." << endl;
			cout << "That word doesn't meet the minimum word length." << endl;
		}else if(usedWords.contains(word)){
			cout << "You've already guessed that!" << endl;
		}else{
			if(!words.contains(word)){
				cout << "You can't make that word!" << endl;
			}else{
				bool isWord = false;
				for(int i = 0; i < boardN; i++){
					for(int j = 0; j < boardN; j++){
						if(!isWord && isWordOnBoard(charBoard, usedChars, word, 0, i, j)){
							isWord = true;
						}
					}
				}
				if(!isWord){
					cout << "You can't make that word!" << endl;
				}else{
					removeHighlights();
					usedWords.add(word);
					recordWordForPlayer(word, HUMAN);
					canFindWord = true;
					break;
				}
			}
		}
		word = getLine("Enter a word: ");
	}
	if(word != ""){
		zeroMatrix(usedChars);
	}
	if(word == ""){
		string answer = getLine("Do you want to use extra helps? ");
		while(answer != "yes" && answer != "no"){
			cout << "Please answer yes or no." << endl;
			answer = getLine("Do you want to use extra helps? ");
		}
		if(answer == "yes" && (SWAP != 0 || BLOCK != 0 || DICTATION != 0)){
			giveHelps(charBoard, usedChars, words, usedWords, canFindWord);
		}
		if(answer == "yes" && SWAP == 0 && BLOCK == 0 && DICTATION == 0){
			cout << "You don't have any helps lefted" << endl;
		}
		cout << endl;
	}
}
/*
 * Function: playerTurn
 * --------------------------
 * Show proper massages for using exta helps.
 */
void giveHelps(Grid<char> &charBoard, Grid<int> &usedChars, Lexicon &words, Set<string> &usedWords, bool &canFindWord){
	cout << "You have:" << endl;
	cout << SWAP << " SWAP lefted." << endl;
	cout << BLOCK << " column BLOCK lefted." << endl;
	cout << DICTATION << " DICTATION lefted." << endl;
	string answer = getLine("Which help do you want to use? ");
	while(toUpperCase(answer) != "SWAP" && toUpperCase(answer) != "BLOCK" && toUpperCase(answer) != "DICTATION"){
			cout << "Please answer SWAP, BLOCK or DICTATION." << endl;
			answer = getLine("Which help do you want to use? ");
	}
	if(toUpperCase(answer) == "SWAP"){
		if(SWAP == 0){
			cout << "You don't have any SWAP lefted." << endl;
			giveHelps(charBoard,usedChars,words,usedWords,canFindWord);
		}else{
			SWAP--;
			int x1 = getInteger("Enter first char Row: ");
			while(!(x1 > 0 && x1 <= boardN)){
				cout << "Please enter number from 1 to " << boardN << "." << endl;
				x1 = getInteger("Enter first char Row: ");
			}
			int y1 = getInteger("Enter first char Column: ");
			while(!(y1 > 0 && y1 <= boardN)){
				cout << "Please enter number from 1 to " << boardN << "." << endl;
				y1 = getInteger("Enter first char Column: ");
			}
			int x2 = getInteger("Enter second char Row: ");
			while(!(x2 > 0 && x2 <= boardN)){
				cout << "Please enter number from 1 to " << boardN << "." << endl;
				x2 = getInteger("Enter second char Row: ");
			}
			int y2 = getInteger("Enter second char Column: ");
			while(!(y2 > 0 && y2 <= boardN)){
				cout << "Please enter number from 1 to " << boardN << "." << endl;
				y2 = getInteger("Enter second char Column: ");
			}
			swap(charBoard, x1-1, y1-1, x2-1, y2-1);
			cout << SWAP << " SWAPS lefted." << endl;
		}
	}
	if(toUpperCase(answer) == "BLOCK"){
		if(BLOCK == 0){
			cout << "You don't have any SWAP lefted." << endl;
			giveHelps(charBoard,usedChars,words,usedWords,canFindWord);
		}else{
			BLOCK--;
			int x = getInteger("Enter column number: ");
			while(!(x > 0 && x <= boardN)){
				cout << "Please enter number from 1 to " << boardN << "." << endl;
				x = getInteger("Enter column number: ");
			}
			blockColumn(usedChars, x-1);
			cout << BLOCK << " BLOCKS lefted." << endl;
		}
	}
	if(toUpperCase(answer) == "DICTATION"){
		if(DICTATION == 0){
			cout << "You don't have any SWAP lefted." << endl;
			giveHelps(charBoard,usedChars,words,usedWords,canFindWord);
		}else{
			DICTATION--;
			string s = dictate(charBoard, usedChars,words, usedWords);
			if(s != ""){
				cout << "Computer dictated word: " << s << "." << endl;
				cout << DICTATION << " DICTATIONS lefted." << endl;
				removeHighlights();
			}else{
				cout << "Computer can't find word." << endl;
				cout << "Game has ended." << endl;
				canFindWord = false;
			}
		}
	}
}
/*
 * Function: removeHighlights
 * --------------------------
 * Clean whole board from highlights.
 */
void removeHighlights(){
	pause(1000);
	for(int i = 0; i < boardN; i++){
		for(int j = 0; j < boardN; j++){
			highlightCube(i,j,false);
		}
	}
}
/*
 * Function: isWordOnBoard
 * --------------------------
 * Check if the word is on the board.
 */
bool isWordOnBoard(Grid<char> &charBoard, Grid<int> usedChars, string word, int index, int x, int y){
	if(index >= word.length()){
		return true;
	}
	if(x < 0 || y < 0 || x > boardN-1 || y > boardN-1){
		return false;
	}
	if(charBoard[x][y] == toupper(word[index]) && usedChars[x][y] < 1){
		usedChars[x][y]++;
		for(int i = x - 1; i <= x+1; i++){
			for(int j = y -1; j <= y+1; j++){
				if(isWordOnBoard(charBoard, usedChars, word, index+1, i, j)){
					highlightCube(x,y,true);
					return true;
				}
			}
		}
	}
	return false;
}
/*
 * Function: generatePlayerBoard
 * --------------------------
 * Generate and display whole user configed board.
 */
void generatePlayerBoard(Grid<char> &charBoard, string &chars){
	for(int i = 0; i < boardN*boardN; i++){
		generateBoardSpot(charBoard, i, chars[i]);
	}
}
/*
 * Function: generateStandardBoard
 * --------------------------
 * Generate and display whole standard board.
 */
void generateStandardBoard(Grid<char> &charBoard){
	for(int i = 0; i < boardN*boardN; i++){
		char ch = randomChar(i);
		generateBoardSpot(charBoard, i, ch);
	}
}
/*
 * Function: generateBoardSpot
 * --------------------------
 * Display character on the board spot.
 * Save information in the grid.
 */
void generateBoardSpot(Grid<char> &charBoard, int &index, char ch){
	int x = index / boardN;
	int y = index % boardN;
	ch = toupper(ch);
	charBoard[x][y] = ch;
	labelCube(x, y, ch);
}
/*
 * Function: randomChar
 * --------------------------
 * Random charachter for board spot.
 */
char randomChar(int &i){
	string cube;
	if(boardN == 4){
		cube = STANDARD_CUBES[i];
	}else{
		cube = BIG_BOGGLE_CUBES[i];
	}
	int index = randomInteger(0, 5);
	return cube[index];
}
/*
 * Function: showMassages
 * --------------------------
 * Show starting massages for user.
 */
void showMassages(Grid<char> &charBoard){
	welcome();
	askInstructions();
	wantBigBoggle();
	Grid<char> charBoardTemp(boardN,boardN);
	charBoard = charBoardTemp;
	drawBoard(boardN,boardN);
	configuration(charBoard);
}
/*
 * Function: welcome
 * -----------------
 * Print out a cheery welcome message.
 */
void welcome() {
    cout << "Welcome!  You're about to play an intense game ";
    cout << "of mind-numbing Boggle.  The good news is that ";
    cout << "you might improve your vocabulary a bit.  The ";
    cout << "bad news is that you're probably going to lose ";
    cout << "miserably to this little dictionary-toting hunk ";
    cout << "of silicon.  If only YOU had a gig of RAM..." << endl << endl;
}

/*
 * Function: askInstructions
 * --------------------------
 * Ask user if he/she wants to print out instructions.
 */
void askInstructions(){
	string answer = getLine("Do you need instructions? ");
	while(answer != "yes" && answer != "no"){
		cout << "Please answer yes or no." << endl;
		answer = getLine("Do you need instructions? ");
	}
	if(answer == "yes"){
		giveInstructions();
	}
	cout << endl;
}
/*
 * Function: giveInstructions
 * --------------------------
 * Print out the instructions for the user.
 */
void giveInstructions() {
    cout << endl;
    cout << "The boggle board is a grid onto which I ";
    cout << "I will randomly distribute cubes. These ";
    cout << "6-sided cubes have letters rather than ";
    cout << "numbers on the faces, creating a grid of ";
    cout << "letters on which you try to form words. ";
    cout << "You go first, entering all the words you can ";
    cout << "find that are formed by tracing adjoining ";
    cout << "letters. Two letters adjoin if they are next ";
    cout << "to each other horizontally, vertically, or ";
    cout << "diagonally. A letter can only be used once ";
    cout << "in each word. Words must be at least four ";
    cout << "letters long and can be counted only once. ";
    cout << "You score points based on word length: a ";
    cout << "4-letter word is worth 1 point, 5-letters ";
    cout << "earn 2 points, and so on. After your puny ";
    cout << "brain is exhausted, I, the supercomputer, ";
    cout << "will find all the remaining words and double ";
    cout << "or triple your paltry score." << endl;
	cout << "You can use 3 extra help, each one for 3 times:" << endl << endl;
	cout << "SWAP: You can swap 2 characters' place." << endl;
	cout << "COLUMN BLOCK: You can block 1 column for opponent for single round." << endl;
	cout << "DICTATION: If you can't figure out words, computer will dictate you the longest one." << endl << endl;
	cout << "Also in each round, randomly one character will be blocked." << endl;
}
/*
 * Function: askConfiguration
 * --------------------------
 * Ask user if he/she wants to config the board.
 */
bool askConfiguration(){
	cout << "I'll give you a chance to set up the board to your specification, which makes it easier to confirm your boggle program is working." << endl;

	string answer = getLine("Do you want to force the board configuration? ");

	while(answer != "yes" && answer != "no"){
		cout << "Please answer yes or no." << endl;
		answer = getLine("Do you want to force the board configuration? ");
	}
	if(answer == "yes"){
		return true;
	}
	if(answer == "no"){
		cout << "Ok, take all the time you want and find all the words you can!  Signal that you're finished by entering an empty line." << endl << endl;
		return false;
	}
	return false;
}
/*
 * Function: configuration
 * --------------------------
 * Config the board.
 */
void configuration(Grid<char> &charBoard){
	if(askConfiguration()){
		string chars = playerConfiguration();
		generatePlayerBoard(charBoard, chars);
	}else{
		generateStandardBoard(charBoard);
	}
	cout << endl;
}
/*
 * Function: playerConfiguration
 * --------------------------
 * Ask user if he/she wants to config the board.
 * If answer is yes, asks for characters to display.
 */
string playerConfiguration(){
	cout << "Enter a " << boardN*boardN << "-character string to identify which letters you want on the cubes." << endl;
	cout << "The first " << boardN << " letters are the cubes on the top row from left to right, the next " << boardN << " letters are the second row, and so on." << endl;
	string chars = getLine("Enter the string: ");
	while(chars.length() != boardN*boardN){
		cout << "String must include " << boardN*boardN << " characters!" << endl;
		chars = getLine("Try again: ");
	}
	return chars;
}
/*
 * Function: wantBigBoggle
 * --------------------------
 * Ask user if he/she wants to play Big Boggle.
 */
void wantBigBoggle(){
	cout << "You can choose standard Boggle (4x4 grid)" << endl;
	cout << "or Big Boggle (5x5)." << endl;
	string answer = getLine("Would you like Big Boggle? ");
	while(answer != "yes" && answer != "no"){
		cout << "Please answer yes or no." << endl;
		answer = getLine("Would you like Big Boggle? ");
	}
	if(answer == "yes"){
		boardN++;
	}
	cout << endl;
}