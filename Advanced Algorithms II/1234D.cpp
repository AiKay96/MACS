// https://codeforces.com/contest/1234/problem/D
// https://codeforces.com/problemset/problem/1234/D

#include <bits/stdc++.h>
using namespace std;
int main(){
  string s;
  cin >> s;
  int q;
  cin >> q;
  set<int> st;
  vector<set<int> > indexes(26, st);
  for(int i = 0; i < s.length(); i++)
    indexes[s[i] - 'a'].insert(i);
  for(int i = 0; i < q; i++){
    int type;
    cin >> type;
    if(type == 1){
      int x;
      cin >> x;
      x--;
      set<int>::iterator it = indexes[s[x]-'a'].find(x);
      indexes[s[x]-'a'].erase(it);
      cin >> s[x];
      indexes[s[x]-'a'].insert(x);
    }else{
      int l, r;
      cin >> l >> r;
      l--;
      r--;
      int diff = 0;
      for(int i = 0; i < 26; i++){
        set<int>::iterator it = indexes[i].lower_bound(l);
        if(it == indexes[i].end())
            continue;
        if(*it <= r)
          diff++;
      }
      cout << diff << endl;
    }
  }
}