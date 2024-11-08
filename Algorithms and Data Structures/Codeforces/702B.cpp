// https://codeforces.com/contest/702/problem/B
// https://codeforces.com/problemset/problem/702/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  int pow2[31];
  pow2[0] = 1;
  for(int i = 1; i <= 30; i++)
    pow2[i] = pow2[i-1] * 2;
  int n;
  cin >> n;
  int arr[n];
  set<int> st;
  map<int, int> mp;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    st.insert(arr[i]);
    if(mp.count(arr[i]))
        mp[arr[i]]++;
    else
        mp[arr[i]] = 1;
  }
  long long ans = 0;
  for(int i = 0; i < n; i++){
    for(int j = 0; j < 31; j++){
      if(st.find(pow2[j]- arr[i]) != st.end()){
          if(arr[i] == pow2[j]- arr[i])
              ans += mp[arr[i]]-1;
          else
              ans += mp[pow2[j]- arr[i]];
      }
    }
  }
  cout << ans / 2<< endl;
}