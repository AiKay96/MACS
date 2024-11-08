// https://codeforces.com/contest/1729/problem/B
// https://codeforces.com/problemset/problem/1729/B

#include <bits/stdc++.h>
using namespace std;
int main(){
  int q;
  cin >> q;
  for(int a = 0; a < q; a++){
      int n;
      cin >> n;
      string t;
      cin >> t;
      string ans = "";
      for(int i = n - 1; i >= 0; i--){
          char c;
          int num;
          if(t[i] == '0'){
              int num1 = t[i-2] - '0';
              int num2 = t[i-1] - '0';
              num = 10*num1 + num2;
              c = 'a' - 1 + num;
              i = i - 2;
          }else{
              num = t[i] - '0';
              c = 'a' - 1 + num;
          }
          string temp = "";
              temp += c;
              temp += ans;
              ans = temp;
      }
      cout << ans << endl;
  }
}