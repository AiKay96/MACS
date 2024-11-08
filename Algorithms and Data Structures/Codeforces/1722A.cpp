// https://codeforces.com/contest/1722/problem/A
// https://codeforces.com/problemset/problem/1722/A

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  string main = "Timur";
  bool used[5];
  for(int i = 0; i < 5; i++)
      used[i] = false;
  for(int a = 0; a < t; a++){
    int n;
    cin >> n;
    
    string s;
    cin >> s;
    if(n != 5)
      cout << "NO" << endl;
    else{
      bool fail = false;
      for(int i = 0; i < n; i++){
        for(int j = 0; j < 5; j++){
          if(s[i] == main[j] && !used[j]){
            used[j] = true;
            break;
          }else if(j == 4){
            cout << "NO" << endl;
            fail = true;
            break;
          }  
        }
        if(fail)
          break;
    	}
        if(!fail)
            cout << "YES" << endl;
      for(int i = 0; i < 5; i++)
        used[i] = false;
    }
  }
}