/*
 * File: NumericConversions.cpp
 * ---------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Numeric Conversions problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include <string>
#include "simpio.h"
#include "console.h"
using namespace std;

/* Function prototypes */

string intToString(int n);
int stringToInt(string str);

string intToString(int n){
	if(n == -2147483648){
		return "-2147483648";
	}
	string result = "";
	if(n == 0){
		return result + '0';
	}
	if(n < 0){
		return "-" + intToString(0 - n);
	}
	if(n / 10 == 0){
		char c = n + '0';
		return result + c;
	}
	char c = n%10 + '0';
	return intToString(n / 10) + c;
}

int stringToInt(string str){
	if(str.length() == 0){
		return 0;
	}
	if(str[0] == '-'){
		return -stringToInt(str.substr(1));
	}
	int length = str.length();
	return 10*stringToInt(str.substr(0, length - 1)) + (str[length - 1] - '0');
}

/* Main program */

int main() {
	cout << intToString(getInteger()) << endl;
	cout << stringToInt(getLine()) << endl;
    return 0;
}
