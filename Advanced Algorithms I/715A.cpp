// https://codeforces.com/contest/715/problem/A
// https://codeforces.com/problemset/problem/715/A

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    long long n;
    cin >> n;
    long long curr = 2;
    for(long long i = 1; i <= n; i++){
        cout << i*(i+1)*(i+1) - (curr/i) << endl;
        curr = i*(i+1);
    }
}