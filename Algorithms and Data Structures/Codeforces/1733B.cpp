// https://codeforces.com/contest/1733/problem/B
// https://codeforces.com/problemset/problem/1733/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
      int n, x, y;
      cin >> n >> x >> y;
      if((x > 0 && y > 0) || (x == 0 && y == 0))
        cout << -1 << endl;
      else{
        int wins = max(x, y);
        int num = (n-1) / wins;
        if((n-1) % wins == 0){
            for(int i = 0; i < n-1; i+=wins){
                for(int j = 0; j < wins; j++){
                    cout << i + 2 << " ";
                }
            }
            cout << endl;
        }else{
            cout << -1 << endl;
        }
      }
  }
}