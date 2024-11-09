// https://codeforces.com/contest/1451/problem/F
// https://codeforces.com/problemset/problem/1451/F

#include <bits/stdc++.h>
using namespace std;

int arr[250];
 
int main(){
	int t;
	cin >> t;
	for(int k = 0; k < t; k++){
		for(int i = 0; i < 250; i++)
		    arr[i] = 0;
		int n, m;
		cin >> n >> m;
		for(int i = 0; i < n; i++){
		    for(int j = 0; j < m; j++){
		        int a;
		        cin >> a;
		        arr[i + j] = arr[i + j] ^ a;
		    }
		}
		int maxi = 0;
		for(int i = 0; i < 250; i++)
		    maxi = max(maxi, arr[i]);
		if(maxi == 0)
			cout << "Jeel" << endl;
		else
			cout << "Ashish" << endl;
	}
}