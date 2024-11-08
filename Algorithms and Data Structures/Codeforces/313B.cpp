// https://codeforces.com/contest/313/problem/B
// https://codeforces.com/problemset/problem/313/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  string s;
  cin >> s;
  int dp[s.length()];
  dp[0] = 0;
  for(int i = 1; i < s.length(); i++){
    if(s[i] == s[i-1])
        dp[i] = dp[i-1] + 1;
    else
        dp[i] = dp[i-1];
  }
  int m;
  cin >> m;
  for(int i = 0; i < m; i++){
      int a, b;
      cin >> a >> b;
      cout << dp[b-1] - dp[a-1] << endl;
  }
}