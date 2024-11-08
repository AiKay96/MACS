/*
 * File: Combinations.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Combinations problem.
 * [TODO: rewrite the documentation]
 */

#include <iostream>
#include "simpio.h"
#include "console.h"
using namespace std;

int C(int n, int k){
	if(k == 0 || n == k){
		return 1;
	}
	return C(n - 1, k - 1) + C(n - 1, k);
}

int main() {
	int n = getInteger("n: ");
	int k = getInteger("k: ");
	cout << C(n,k) << endl;
    return 0;
}
