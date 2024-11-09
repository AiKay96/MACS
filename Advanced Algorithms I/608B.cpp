// https://codeforces.com/contest/608/problem/B
// https://codeforces.com/problemset/problem/608/B

#include <bits/stdc++.h>
using namespace std;
          
int main(){
    string a, b;
    cin>> a >>b;
    long long dp[b.length() + 1];
    dp[0] = 0;
    for(int i = 0; i < b.length(); i++)
        dp[i+1] = dp[i] + b[i] - '0';
    long long diff = b.length() - a.length();
    long long sum = 0;
    for(int i = 0; i < a.length(); i++){
        if(a[i]=='0')
            sum += dp[i + diff + 1] - dp[i];
        else
            sum += diff + 1 - (dp[i + diff + 1] - dp[i]);
    }
    cout << sum << endl; 
}