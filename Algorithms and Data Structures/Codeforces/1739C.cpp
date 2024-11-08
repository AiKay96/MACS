// https://codeforces.com/contest/1739/problem/C
// https://codeforces.com/problemset/problem/1739/C

#include <bits/stdc++.h>
using namespace std;
long long dp[2][61];
long long mod = 998244353;
long long powN(int n, long long x);
long long C(long long m, long long n);
long long factorial[61];
int main(){
    factorial[0] = 1;
    for(int i = 1; i <= 60; i++)
        factorial[i] = (factorial[i-1]*i)%mod;
    dp[0][2] = 1;
    dp[1][2] = 0;
    for(int i = 4; i <= 60; i+=2){
        dp[0][i] = (C(i/2, i-1) + dp[1][i-2])%mod;
        dp[1][i] = (C(i/2, i-2) + dp[0][i-2])%mod;
    }
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        int n;
        cin >> n;
        cout << dp[0][n] << " " << dp[1][n] << " 1" << endl;
    }
}
long long powN(int n, long long x){
    if(n == 0)
        return 1;
    if(n % 2 == 0){
        long long a = powN(n/2, x);
        return (a*a) % mod;
    }else{
        long long a = powN(n-1, x);
        return (a*x) % mod;
    }
}
long long C(long long m, long long n){
    long long ans = (long long)(factorial[n] * powN(mod - 2, factorial[m]))%mod;
    ans = (long long)(ans * powN(mod - 2, factorial[n - m]))%mod;
    return ans;
}