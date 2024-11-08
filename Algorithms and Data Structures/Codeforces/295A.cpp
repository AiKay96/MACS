// https://codeforces.com/contest/295/problem/A
// https://codeforces.com/problemset/problem/295/A

#include <bits/stdc++.h>
using namespace std;
int main(){
  int n, m, k;
  cin >> n >> m >> k;
  long long arr[n], l[m], r[m], d[m];
  for(int i = 0; i < n; i++)
    cin >> arr[i];
  for(int i = 0; i < m; i++)
    cin >> l[i] >> r[i] >> d[i];
  vector<int> queries(m+1, 0);
  for(int i = 0; i < k; i++){
      int a, b;
      cin >> a >> b;
      queries[a-1]++;
      queries[b]--;
  }
  for(int i = 1; i < m; i++)
      queries[i] += queries[i-1];
  vector<long long> dp(n+1, 0);
  for(int i = 0; i < m; i++){
      dp[l[i] - 1] += queries[i]*d[i];
      dp[r[i]] -= queries[i]*d[i];
  }
  for(int i = 1; i < n; i++)
      dp[i] += dp[i-1];
  for(int i = 0; i < n; i++){
      dp[i] += arr[i];
      cout << dp[i] << " ";
  }
  cout << endl;
}