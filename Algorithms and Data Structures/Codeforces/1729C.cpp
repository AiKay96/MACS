// https://codeforces.com/contest/1729/problem/C
// https://codeforces.com/problemset/problem/1729/C

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
      string s;
      cin >> s;
      vector<pair<int, int> > v;
      for(int i = 0; i < s.length(); i++){
          pair<int, int> tmp;
          tmp.first = s[i] - 'a';
          tmp.second = i;
          v.push_back(tmp);
      }
      sort(v.begin(), v.end());
      int ind1 = -1;
      int ind2 = 0;
      int end = 0;
      for(int i = 0; i < s.length(); i++){
          if(s[0] - 'a' == v[i].first){
              if(ind1 == -1)
                ind1 = i;
            ind2 = i;
          }
          if(s[s.length() - 1] - 'a' == v[i].first)
            end = i;
      }
      string ans = "";
      int jumps = 0;
      int cost = 0;
      if(ind1 < end){
          cost = abs(v[ind1].first - v[end].first);
          for(int i = ind1; i <= end; i++){
              int index = v[i].second + 1;
              ans += std::to_string(index);
              ans+= " ";
              jumps++;
          }
      }else{
          cost = abs(v[ind2].first - v[end].first);
          ans += "1 ";
          jumps++;
          for(int i = ind2; i > end; i--){
              if(i == ind1)
              continue;
              int index = v[i].second + 1;
              ans += std::to_string(index);
              ans += " ";
              jumps++;
          }
          int x = end - 1;
          while(x >= 0 && v[x].first == v[end].first){
              x--;
          }
          for(int i = x+ 1; i <= end; i++){
              int index = v[i].second + 1;
              ans += std::to_string(index);
              ans += " ";
              jumps++;
          }
      }
      cout << cost << " " << jumps << endl;
      cout << ans << endl;
  }
}