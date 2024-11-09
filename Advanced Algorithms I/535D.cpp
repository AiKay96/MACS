// https://codeforces.com/contest/535/problem/D
// https://codeforces.com/problemset/problem/535/D

#include<bits/stdc++.h>
using namespace std;
long long p = 1000000007;
int n, m;
string s;
vector<int> z_function(string s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
int main(){
  	ios_base::sync_with_stdio(false);
	cin >> n >> m;
	cin >> s;
	vector<int> z = z_function(s);
	int prev, empty;
	cin >> prev;
	prev--;
	empty = prev;
	for (int i = 1; i < m; ++i) {
	    int curr;
		cin >> curr;
		curr--;
		if (curr - prev >= s.length()){
			empty += curr - (prev + s.length());
		}else {
			if (z[curr - prev] != prev + s.length() - curr) {
				cout << 0 << endl;
				return 0;
			}
		}
		prev = curr;
	}
	empty += n - (prev + s.length());
	if (m == 0) 
		empty = n;
	if (empty == 0) {
		cout << 1 << endl;
		return 0;
	}
	long long ans = 1;
	for (int i = 0; i < empty; i++) 
		ans = (ans * 26) % p;
	cout << ans;
}