// https://codeforces.com/contest/1841/problem/D
// https://codeforces.com/problemset/problem/1841/D

#include<bits/stdc++.h>
using namespace std;
multiset<pair<int, int>> st;
int main() {
    int t, n, l, r;
    bool seg;
    
    cin >> t;
    for(int k = 0; k < t; k++) {
        cin >> n; 
        st.clear(); 
        int limit = -1;
        int last = -1;
        seg = false;
        for (int i = 1; i <= n; i++) {
            cin >> l >> r;
            st.insert({r, l});
        }
        for (auto curr : st) {
            if (curr.second <= limit)
				continue;
            if (!seg) {            
                seg = true; 
                last = curr.first;
            } else {
                if (curr.second <= last) {
                    seg = false; 
                    n -= 2; 
                    limit = curr.first;
                } else {
                    last = curr.first;
                }
            }
        }
        cout << n << endl;
    }
}