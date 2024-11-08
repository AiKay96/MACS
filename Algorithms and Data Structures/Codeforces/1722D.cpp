// https://codeforces.com/contest/1722/problem/D
// https://codeforces.com/problemset/problem/1722/D

#include <bits/stdc++.h>
using namespace std;
int main(){
  int t;
  cin >> t;
  for(int a = 0; a < t; a++){
    int n;
    cin >> n;
    
    vector<long long> points;
    long long ans = 0;
    for(int i = 0; i < n; i++){
        char c;
        cin >> c;
        if(c == 'L')
            points.push_back(i);
        else
            points.push_back(n - 1 - i);
        ans += points[i];
    }
    sort(points.begin(), points.end());
    for(int i = 0; i < n; i++){
        if(points[i] < n - 1 - points[i]){
            ans = ans - points[i] + n - 1 - points[i];
        }
        cout << ans << " ";
    }
    cout << endl;
  }
}