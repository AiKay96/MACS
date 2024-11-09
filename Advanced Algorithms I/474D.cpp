// https://codeforces.com/contest/474/problem/D
// https://codeforces.com/problemset/problem/474/D

#include <bits/stdc++.h>
using namespace std;
long long p = 1000000007;
long long dp[100001];
int main(){
    ios_base::sync_with_stdio(false);
    dp[0] = 1;
    int t, k;
    cin >> t >> k;
    for(int i = 1; i <= 100000; i++){
        dp[i] = (dp[i] + dp[i-1]) % p;
        if(i-k >= 0)
            dp[i] = (dp[i] + dp[i-k]) % p;
    }
    dp[0] = 0;
    for(int i = 1; i <= 100000; i++)
        dp[i] = (dp[i] + dp[i-1]) % p;
    for(int i = 0; i < t; i++){
        int a, b;
        cin >> a >> b;
        cout << (dp[b] - dp[a-1] + p) % p << endl;
    }
}