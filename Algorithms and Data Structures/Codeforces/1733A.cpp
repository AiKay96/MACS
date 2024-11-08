// https://codeforces.com/contest/1733/problem/A
// https://codeforces.com/problemset/problem/1733/A

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
      int n, k;
      cin >> n >> k;
      long long arr[n];
      for(int i = 0; i < n; i++)
        cin >> arr[i];
      long long ans = 0;
      long long dp[k];
      for(int i = 0; i < k; i++)
        dp[i] = 0;
      for(int i = 0; i < k; i++){
          for(int j = i; j < n; j+=k)
            dp[i] = max(dp[i], arr[j]);
          ans += dp[i];
      }
      cout << ans << endl;
  }
}