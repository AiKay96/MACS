// https://codeforces.com/contest/1772/problem/A
// https://codeforces.com/problemset/problem/1772/A

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b;
string s;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> s;
        cout << s[0] + s[2] - '0' - '0' << endl;
    }
}