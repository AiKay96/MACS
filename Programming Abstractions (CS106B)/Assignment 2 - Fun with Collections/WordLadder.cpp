/*
 * File: WordLadder.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Word Ladder problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
#include "lexicon.h"
#include "queue.h"
#include "map.h"
#include "stack.h"
using namespace std;

void generateNewWord(string& temp, string& midWord, Queue<string>& q, Map<string, string>& map, Lexicon& words){
	for(int i = 0; i < midWord.length(); i++){
		for(char j = 'a'; j <= 'z'; j++){
			//if word isn't same.
			if(temp[i] != j){
				midWord[i] = j;
				//if word is in lexicon and we don't generate it already, it should be added in queue for bfs and map for data.
				if(words.contains(midWord) && !map.containsKey(midWord)){
					q.enqueue(midWord);
					map.put(midWord, temp);
				}
			}
		}
		//after changing chars on certain index, word should return to its first face.
		midWord = temp;
	}
}

void bfs(string& startingWord, string& endingWord, Map<string, string>& map, Lexicon& words){
	Queue<string> q;

	//starting bfs.
	q.enqueue(startingWord);
	//saving data in map to build path in the end. key = word and value = word's "parent" / from where it came.
	map.put(startingWord, "");

	//while queue isn't empty or we didn't find the target/ending word, we should generate new ladder steps.
	while(!q.isEmpty()){
		string midWord = q.dequeue();
		string temp = midWord;
		//if we found target/ending word, while should break.
		if(midWord == endingWord){
			break;
		}
		//generating new ladder words.
		generateNewWord(temp, midWord, q, map, words);
	}
}

void printPath(string& startingWord, string& endingWord, Map<string, string>& map){
	Stack<string> wordLadder;

	string word = endingWord;

	//if we found ladder
	if(map.containsKey(word)){
		//starting building path from ending and putting steps in stack.
		while(word != startingWord){
			wordLadder.push(word);
			word = map.get(word);
		}
		cout << "Ladder found: " << startingWord;
		//printing ladders correctly.
		while(!wordLadder.isEmpty()){
			cout << " -> " << wordLadder.pop();
		}
		cout << endl;
	}else{
		cout << "No word ladder could not be found." << endl;
	}
}

int main() {
    Lexicon words("EnglishWords.dat");
	while(true){
		Map<string,string> map;

		//gathering inputs and printing messages.
		string startingWord = getLine("Enter the starting word (or nothing to quit): ");
		if(startingWord == ""){
			cout << "Goodbye!" << endl;
			break;
		}
		string endingWord = getLine("Enter the ending word: ");
		cout << "Searching..." << endl;

		//if words length is different or they aren't in the lexicon no ladder couldn't be found.
		if(!(words.contains(startingWord) && words.contains(endingWord)) || startingWord.length() != endingWord.length()){
			cout << "No word ladder could not be found." << endl;
		}else{
			bfs(startingWord, endingWord, map, words);
			printPath(startingWord, endingWord, map);
		}
	}
    return 0;
}
