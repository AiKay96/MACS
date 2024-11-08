/*
 * File: RandomWriter.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Random Writer problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "map.h"
#include "vector.h"
#include "random.h"
using namespace std;

void processFile(ifstream& input, int& MarkovOrder, Map<string,Vector<char> >& map, string& key, string& text){
	char c;
	//building first string.
	for(int i = 0; i < MarkovOrder; i++){
		input.get(c);
		key += c;
	}
	int size = INT_MIN;
	while(input.get(c)){
		//putting in map key and next char.
		if(!map.containsKey(key)){
			Vector<char> value;
			map.put(key, value);
		}
		map[key].add(c);

		//checking which key is more common to use for starting word.
		int keySize = map[key].size();
		if(size < keySize){
			size = keySize;
			text = key;
		}

		//generating new key.
		key = key.substr(1);
		key += c;
	}
}
void generateText(string& key, string& text, int& MarkovOrder, Map<string,Vector<char> >& map){
	int charNums = 2000;

	//while text length is enough we should gather chars.
	while(text.length() <= charNums){
		key = text.substr(text.length() - MarkovOrder);
		//if this key is only used in end of the text.
		if(map[key].size() == 0){
			break;
		}
		//randoming next char and adding it to the text.
		int randChar = randomInteger(0, map[key].size() - 1);
		text+= map[key][randChar];
	}
	cout << text << endl;
}
void getData(ifstream& input, int& MarkovOrder){
	//gathering inputs and printing messages.
	string filename = getLine("Enter the source text: ");
	input.open(filename.c_str());
	while(!input.is_open()){
		input.clear();
		cout << "Unable to open that file. Try again." << endl;
		filename = getLine("Enter the source text: ");
		input.open(filename.c_str());
	}

	MarkovOrder = getInteger("Enter the Markov order [1-10]: ");
	while(MarkovOrder > 10 || MarkovOrder < 1){
		cout << "That value is out of range." << endl;
		MarkovOrder = getInteger("Enter the Markov order [1-10]: ");
	}
	cout << "Processing file..." << endl;
}

int main() {
	Map<string,Vector<char> > map;
	ifstream input;
	int MarkovOrder;
	getData(input, MarkovOrder);
	string key = "";
	string text = "";
	processFile(input, MarkovOrder, map, key, text);
	generateText(key, text, MarkovOrder, map);

    return 0;
}
