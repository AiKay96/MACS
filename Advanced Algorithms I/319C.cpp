// https://codeforces.com/contest/319/problem/C
// https://codeforces.com/problemset/problem/319/C

#include <bits/stdc++.h>
using namespace std;

int a[100010], b[100010], arr[100010];
long long dp[100010];

int main(){
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> a[i];
    for(int i = 1; i <= n; i++)
        cin >> b[i];
    int t = 1;
    int h = 1;
    arr[1] =  1;
    for(int i =2 ; i <= n; i++){
        while(h < t && dp[arr[h+1]] - dp[arr[h]] <= (long long)a[i] * (b[arr[h]] - b[arr[h+1]]))
            h++;
        dp[i] = (long long)a[i] * b[arr[h]] + dp[arr[h]];
        while(h < t && (double)(dp[arr[t]]- dp[arr[t - 1]]) / (b[arr[t - 1]]-b[arr[t]]) >= (double)(dp[i] - dp[arr[t]]) / (b[arr[t]] - b[i]))
            t--;
        t++;
        arr[t]=i;
    }
    cout << dp[n] << endl;
    return 0;
} 