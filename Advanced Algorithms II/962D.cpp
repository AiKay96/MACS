// https://codeforces.com/contest/962/problem/D
// https://codeforces.com/problemset/problem/962/D

#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;
	cin >> n;
	multiset<pair<long long, long long> > st;
	for(int i = 0; i < n; i++){
		int x;
		cin >> x;
		st.insert({x,i});
	}
	
	vector<pair<long long, long long> > ans;
	set<pair<long long, long long> >::iterator it;
	
	while(st.size() >= 2){
		it = st.begin();
		pair<long long, long long> f = *it;
		st.erase(it);
		
		it = st.begin();
		pair<long long, long long> n = *it;
		
		if(f.first != n.first){
			ans.push_back({f.second, f.first});
		} else {
			st.insert({2 * f.first, n.second});
			st.erase(it);
		}
	}
	it = st.begin();
	pair<long long, long long> f = *it;
	ans.push_back({f.second, f.first});
	sort(ans.begin(), ans.end());
	
	cout<< ans.size() <<endl;
	for(int i = 0; i < ans.size(); i++)
	    cout << ans[i].second << " ";
}