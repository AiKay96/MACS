/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, int numHospitals, Vector< Set<string> >& result, int i){
	//to check every hospital from vector locations, I added parameter int i which is index of hospital.
	//i should be in vector size range and we can't use more than numHospitals hospitals, so it can't become lower than 0.
	if(i == locations.size() || numHospitals == 0){
		//checking if we have covered whole city
		if(cities.isEmpty()){
			return true;
		}else{
			return false;
		}
	}
	//on each index of locations / on each hospital we have 2 cases. to build this hospital or not.
	//temp collections are collections where hospitals are built.
	Set<string> tempCities = cities; //uncovered cities
	Vector< Set<string> > tempResult = result; //hospital list
	//hospital is built, so we should add it to result.
	tempResult.push_back(locations[i]);

	/* checking every city which can be covered from built hospital and deleting them from set, becouse it's 
	 * already covered and don't necessarly needs second hospital. if set go empty that means every city is covered.*/
	foreach(string s in locations[i]){
		if(tempCities.contains(s)){
			tempCities -= s;
		}
	}
	//return case were we have built hospital on i index, or where we haven't
	return canOfferUniversalCoverage(tempCities, locations, numHospitals - 1, tempResult, i+1)
		|| canOfferUniversalCoverage(cities, locations, numHospitals, result, i+1);
}


int main() {
	//int i should start from 0. it is index.
    canOfferUniversalCoverage(cities, locations, numHospitals, result, 0);
    return 0;
}
