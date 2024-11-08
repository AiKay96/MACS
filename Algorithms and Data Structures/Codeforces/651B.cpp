// https://codeforces.com/contest/651/problem/B
// https://codeforces.com/problemset/problem/651/B

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int maxD = INT_MIN;
    map<int, int> mp;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        mp[a]++;
        maxD = max(maxD, mp[a]);
    }
    cout << n - maxD << endl;
}