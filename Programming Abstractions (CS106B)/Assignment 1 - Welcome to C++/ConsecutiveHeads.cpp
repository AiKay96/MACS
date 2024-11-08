/*
 * File: ConsecutiveHeads.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Consecutive Heads problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "random.h"
#include "console.h"
using namespace std;

int flippingCoins(){
	int flipsN = 0;
	int isHeads = 0;
	while(true){
		bool coin = randomChance(0.5);
		if(coin){
			cout << "tails" << endl;
			isHeads = 0;
		}
		if(!coin){
			cout << "heads" << endl;
			isHeads++;
		}
		flipsN++;
		if(isHeads == 3){
			cout << "It took " << flipsN << " flips to get 3 consecutive heads." << endl;
			break;
		}
	}
	return 0;
}

int main() {
    flippingCoins();
    return 0;
}
