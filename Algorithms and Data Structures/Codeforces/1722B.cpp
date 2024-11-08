// https://codeforces.com/contest/1722/problem/B
// https://codeforces.com/problemset/problem/1722/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
    int n;
    cin >> n;
    
    string row1;
    cin >> row1;
    
    string row2;
    cin >> row2;
    
    for(int i = 0; i < n; i++){
        if(row1[i] == 'G')
            row1[i] = 'B';
        if(row2[i] == 'G')
            row2[i] = 'B';
    }
    
    if(row1 == row2)
        cout << "YES" << endl;
    else
        cout << "NO" << endl;
    
  }
}