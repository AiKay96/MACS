/*
 * File: Subsequences.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Subsequences problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "console.h"
#include "simpio.h"
using namespace std;

/* Given two strings, returns whether the second string is a
 * subsequence of the first string.
 */
bool isSubsequence(string text, string subsequence){
	//if entered subsequence is empty answer is true.
	if(subsequence == ""){
		return true;
	}
	//we should find first letter of subsequence in text and then check if lefted letters are on right side.
	int index = text.find(subsequence[0]);
	//if char can be found
	if(index != string::npos){
		//do same for word from this char to the right side.
		return isSubsequence(text.substr(index), subsequence.substr(1));
	}
	return false;
}

int main() {
	string text = getLine("text: ");
	string subsequence = getLine("subString: ");
	cout << isSubsequence(text, subsequence) << endl;
    return 0;
}
