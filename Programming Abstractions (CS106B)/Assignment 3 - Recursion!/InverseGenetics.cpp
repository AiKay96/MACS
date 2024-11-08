/*
 * File: InverseGenetics.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Inverse Genetics problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: listAllRNAStrandsFor(string protein,
 *                                Map<char, Set<string> >& codons);
 * Usage: listAllRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, lists all possible RNA strands that could generate
 * that protein
 */
void listAllRNAStrandsFor(string protein, Map<char, Set<string> >& codons, string result){
	int length = protein.length();
	//if length is 0, that means that we have finished recursion and should print result
	if(length == 0){
		cout << result << endl;
	}
	if(length > 0){
		//Acodons are amino acids of protein first char
		Set<string> Acodons = codons.get(protein[0]);
		//deleting first char
		protein = protein.substr(1);
		string temp = result;
		//for evere amino acid we should make new recipe
		foreach(string s in Acodons){
			result += s;
			listAllRNAStrandsFor(protein, codons, result);
			result = temp;
		}
	}
}

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
    /* Load the codon map. */
    Map<char, Set<string> > codons = loadCodonMap();
	//gathering information
	string protein = getLine("Protein: ");
	string result = "";

	listAllRNAStrandsFor(protein, codons, result);
    return 0;
}

/* You do not need to change this function. */
Map<char, Set<string> > loadCodonMap() {
    ifstream input("codons.txt");
    Map<char, Set<string> > result;

    /* The current codon / protein combination. */
    string codon;
    char protein;

    /* Continuously pull data from the file until all data has been
     * read.
     */
    while (input >> codon >> protein) {
        result[protein] += codon;
    }

    return result;
}
