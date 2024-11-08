// https://codeforces.com/contest/1795/problem/C
// https://codeforces.com/problemset/problem/1795/C

#include <bits/stdc++.h>
using namespace std;
int n, k;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        long long a[n], b[n], pref[n];
        for(int i = 0; i < n; i++)
            cin >> a[i];
        for(int i = 0; i < n; i++)
            cin >> b[i];
        set<pair<long long, int> > st;
        set<pair<long long, int> >::iterator it;
        pref[0] = b[0];
        st.insert({pref[0], 0});
        for(int i = 1; i < n; i++){
            pref[i] = pref[i-1] + b[i];
            st.insert({pref[i], i});
        }
        int seg[n + 1];
        long long minus[n + 1];
        for(int i = 0; i <= n; i++)
            seg[i] = 0;
        for(int i = 0; i <= n; i++)
            minus[i] = 0;
        for(int i = 0; i < n; i++){
            seg[i]++;
            pair<long long, int> search = {a[i], 0};
            if(i != 0)
                search.first += pref[i-1];
            it = st.lower_bound(search);
            if(it != st.end()){
                pair<long long, int> curr = *it;
                seg[curr.second + 1]--;
                if(curr.first != search.first)
                    minus[curr.second] += search.first - curr.first;
            }
        }
        for(int i = 1; i < n; i++)
            seg[i] = seg[i-1] + seg[i];
        for(int i =0; i < n; i++)
            cout << seg[i]*b[i] + minus[i] << " ";
        cout << endl;
    }
}