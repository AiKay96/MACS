// https://codeforces.com/contest/1795/problem/B
// https://codeforces.com/problemset/problem/1795/B

#include <bits/stdc++.h>
using namespace std;
int n, k;
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n >> k;
        vector<pair<int, int> > v;
        for(int i = 0; i < n; i++){
            int a, b;
            cin >> a >> b;
            if(a <= k && k <= b)
                v.push_back({a, b});
        }
        if(v.size() == 0){
            cout << "NO" << endl;
            continue;
        }
        int start = v[0].first;
        int end = v[0].second;
        for(int i = 1; i < v.size(); i++){
            start = max(start, v[i].first);
            end = min(end, v[i].second);
        }
        if(start == end)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}