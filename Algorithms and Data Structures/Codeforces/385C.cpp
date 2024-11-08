// https://codeforces.com/contest/385/problem/C
// https://codeforces.com/problemset/problem/385/C

#include <bits/stdc++.h>
using namespace std;
int main(){
  int n;
  cin >> n;
  int arr[n];
  int Nmax = INT_MIN;
  for(int i = 0; i < n; i++){
      int x;
      scanf("%d", &x);
      arr[i] = x;
      Nmax = max(Nmax, arr[i]);
  }
  vector<int> num(Nmax+1, 0);
  for (long long i = 2; i <= sqrt(Nmax); i++){
        if (num[i] == 0){
            for (int j = i * i; j <= Nmax; j += i){
                if (num[j] == 0)
                    num[j] = i;
            }
        }
  }
  vector<int> sums(Nmax + 1, 0);
  for(int i = 0; i < n; i++){
      set<int> st;
      int number = arr[i];
      if(number <= 1)
        continue;
      while(true){
          if(num[number] == 0){
              if(st.find(number) == st.end())
                sums[number]++;
              break;
          }
          if(st.find(num[number]) == st.end()){
              sums[num[number]]++;
              st.insert(num[number]);
          }
          number = number / num[number];
      }
  }
  for(int i = 1; i <= Nmax; i++)
      sums[i] += sums[i-1];
  int m;
  cin >> m;
  for(int i = 0; i < m; i++){
      int l, r;
      cin >> l >> r;
      if(l > Nmax)
        cout << 0 << endl;
      else{
          r = min(Nmax, r);
        cout << sums[r] - sums[l-1] << endl;
      }
  }
}