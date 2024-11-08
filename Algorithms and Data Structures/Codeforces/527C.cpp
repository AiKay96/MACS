// https://codeforces.com/contest/527/problem/C
// https://codeforces.com/problemset/problem/527/C

#include <bits/stdc++.h>
using namespace std;
int main(){
  int w, h, n;
  cin >> w >> h >> n;
  set<int> x;
  set<int> y;
  multiset<int> xCut;
  multiset<int> yCut;
  
  x.insert(0);
  x.insert(w);
  y.insert(0);
  y.insert(h);
  xCut.insert(w);
  yCut.insert(h);
  
  for(int i = 0; i < n; i++){
    char type;
    cin >> type;
    if(type == 'V'){
      int X;
      cin >> X;
      set<int>::iterator it = x.upper_bound(X);
      int r = *it;
      it--;
      int l = *it;
      xCut.insert(X - l);
      xCut.insert(r - X);
      x.insert(X);
      it = xCut.find(r - l);
      xCut.erase(it);
    }else{
      int Y;
      cin >> Y;
      set<int>::iterator it = y.upper_bound(Y);
      int d = *it;
      it--;
      int u = *it;
      yCut.insert(Y - u);
      yCut.insert(d - Y);
      y.insert(Y);
      it = yCut.find(d - u);
      yCut.erase(it);
    }
    set<int>::iterator it = xCut.end();
    it--;
    int W = *it;
    it = yCut.end();
    it--;
    int H = *it;
    cout << (long long)W*H << endl;
  }
}