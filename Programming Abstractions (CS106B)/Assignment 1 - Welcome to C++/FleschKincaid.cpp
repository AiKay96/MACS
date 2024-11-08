/*
 * File: FleschKincaid.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Flesch-Kincaid problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "tokenscanner.h"

using namespace std;
bool checkSentences(string token){
	if(token == "." || token == "?" || token == "!"){
		return true;
	}
	return false;
}

bool checkWords(string token){
	if(isalpha(token[0])){
		return true;
	}
	return false;
}
int checkSyllables(string token){
	int n = token.length();
	int numSyllables = 0;

	bool isSyllable = false;
	bool isPrevousSyllable = false;

	for(int i = 0; i < n; i++){
		if(token[i] == 'a' || token[i] == 'e' || token[i] == 'i' || token[i] == 'o' || token[i] == 'u' || token[i] == 'y' || 
			token[i] == 'A' || token[i] == 'E' || token[i] == 'I' || token[i] == 'O' || token[i] == 'U' || token[i] == 'Y'){
			isSyllable = true;
			if(!((token[i] == 'e' || token[i] == 'E') && i == n - 1)){
				numSyllables++;
				if(isPrevousSyllable && isSyllable){
					numSyllables--;
				}	
			}
			
		}

		isPrevousSyllable = isSyllable;
		isSyllable = false;

	}

	if(numSyllables == 0){
		numSyllables++;
	}

	return numSyllables;
}

int main() {
	double C0 = -15.59;
	double C1 = 0.39;
	double C2 = 11.8;

	string filename = getLine("file name: ");
	ifstream input(filename.c_str());
	while(!input.is_open()){
		input.clear();
		filename = getLine("enter correct name: ");
		input.open(filename.c_str());
	}

	TokenScanner scanner(input);
	scanner.ignoreWhitespace();
	scanner.addWordCharacters("'");

	int numSentences = 0;
	int numWords = 0;
	int numSyllables = 0;

    while (scanner.hasMoreTokens()) {
      string token = scanner.nextToken();
	  if(checkSentences(token)){
		  numSentences++;
	  }else if(checkWords(token)){
		  numWords++;
		  numSyllables += checkSyllables(token);
	  }
    }
	if(numWords == 0){
		numWords++;
	}
	if(numSentences == 0){
		numSentences++;
	}

	double grade = C0 + C1*(numWords* 1.0/numSentences) + C2*(numSyllables * 1.0 /numWords);

	cout << "Words: " << numWords << endl;
	cout << "Syllables: " << numSyllables << endl;
	cout << "Sentences: " << numSentences << endl;
	cout << "Grade: " << grade << endl;

    return 0;
}
