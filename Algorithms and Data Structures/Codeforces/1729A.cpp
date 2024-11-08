// https://codeforces.com/contest/1729/problem/A
// https://codeforces.com/problemset/problem/1729/A

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int i = 0; i < t; i++){
      int a;
      int b;
      int c;
      cin >> a;
      cin >> b;
      cin >> c;
      
      int way1 = a - 1;
      int way2 = abs(c - b) + c - 1;
      
      if(way1 == way2)
        cout << 3 << endl;
        else if(way1 < way2)
        cout << 1 << endl;
        else
        cout << 2 << endl;
  }
}