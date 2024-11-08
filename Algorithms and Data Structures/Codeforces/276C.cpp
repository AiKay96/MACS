// https://codeforces.com/contest/276/problem/C
// https://codeforces.com/problemset/problem/276/C

#include <bits/stdc++.h>
using namespace std;
int main(){
  int n, q;
  cin >> n >> q;
  int vec[n];
  for(int i = 0; i < n; i++)
      cin >> vec[i];
  vector<long long> v(n+1, 0);
  for(int i = 0; i < q; i++){
      int a, b;
      cin >> a >> b;
      v[a-1]++;
      v[b]--;
  }
  long long dp[n];
  dp[0] = v[0];
  for(int i = 1; i < n; i++)
      dp[i] = dp[i-1] + v[i];
  sort(vec, vec+n);   
  sort(dp, dp+n);
  long long ans = 0;
  for(int i = 0; i < n; i++)
      ans += dp[i]*vec[i];
  cout << ans << endl;
}