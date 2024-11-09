// https://codeforces.com/contest/1194/problem/D
// https://codeforces.com/problemset/problem/1194/D

#include <bits/stdc++.h>
using namespace std;

int main(){
	int t;
	cin >> t;
	for(int i = 0; i < t; i++){
	    int n, k;
	    cin >> n >> k;
	    if(n == 0){
	        cout << "Bob" << endl;
	        continue;
	    }
	    if(k % 3 != 0){
	        if(n % 3 == 0)
	            cout << "Bob" << endl;
	        else
	            cout << "Alice" << endl;
	    }else{
	        int tmp = n / (k + 1);
	        int temp = n - tmp * (k + 1);
	        if(temp % 3 == 0 && temp != k)
	            cout << "Bob" << endl;
	        else
	            cout << "Alice" << endl;
	    }
	}
}