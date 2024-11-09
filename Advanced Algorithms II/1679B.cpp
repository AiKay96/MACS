// https://codeforces.com/contest/1679/problem/B
// https://codeforces.com/problemset/problem/1679/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  int n, q;
  cin >> n >> q;
  int arr[n];
  long long sum = 0;
  for(int i = 0; i < n; i++){
    cin >> arr[i];
    sum += arr[i];
  }
  vector<int> operations(n, 0);
  int lastNum = -1;
  int lastInd = -1;
  for(int i = 1; i <= q; i++){
    int type;
    cin >> type;
    if(type == 1){
      int ind, x;
      cin >> ind >> x;
      ind--;
      if(lastInd > operations[ind])
        sum -= lastNum;
      else
        sum -= arr[ind];
      sum += x;
      arr[ind] = x;
      operations[ind] = i;
    }else{
      cin >> lastNum;
      lastInd = i;
      sum = (long long) lastNum * n;
    }
    cout << sum << endl;
  }
}