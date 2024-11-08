// https://codeforces.com/contest/1725/problem/H
// https://codeforces.com/problemset/problem/1725/H

#include <bits/stdc++.h>
using namespace std;
int main(){
    int N;
	cin >> N;
	vector<int> v;
	int ones = 0;
	for(int h = 0; h < N; h++){
		int a;
		cin >> a;
		if(a%3 == 0)
			a = 0;
		else
			a = 1;
		v.push_back(a);
		ones+=a;
	}
	if(ones*2 >= N){
		ones = N/2;
		cout << 0 << endl;
		for(int i = 0; i < N; i++){
			if(v[i] == 1 && ones > 0){
				cout << 1;
				ones--;
			}else
				cout << 0;
		}
		cout << endl;
	}else{
		ones = N/2;
		cout << 2 << endl;
		for(int i = 0; i < N; i++){
			if(v[i] == 0 && ones > 0){
				cout << 1;
				ones--;
			}else
				cout << 0;
		}
		cout << endl;
	}
}