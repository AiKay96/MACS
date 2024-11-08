// https://codeforces.com/contest/1730/problem/A
// https://codeforces.com/problemset/problem/1730/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
	cin >> t;
	for(int h = 0; h < t; h++){
		int n, c;
		cin >> n >> c;
		vector<int> v;
		map<int, int> mp;
		for(int i = 0; i < n; i++){
			int a;
			cin >> a;
			if(!mp.count(a))
				v.push_back(a);
			mp[a]++;
		}
		int ans = 0;
		for(int i = 0; i < v.size(); i++)
			ans += min(mp[v[i]], c);
		cout << ans << endl;
	}
}