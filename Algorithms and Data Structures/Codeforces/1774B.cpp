// https://codeforces.com/contest/1774/problem/B
// https://codeforces.com/problemset/problem/1774/B

#include <bits/stdc++.h>
using namespace std;
long long t, n, m, k, a, b, arr[100001];
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n >> m >> k;
        bool ans = true;
        for(int i = 0; i < m; i++){
            cin >> arr[i];
        }
        sort(arr, arr+m);
        int ind = 0;
        for(int i = m-1; i >= 0; i--){
           int ujrebi = ind + (arr[i] - 1) * k + 1;
           if(ujrebi > n){
               ans = false;
               break;
           }
           ind++;
        }
        if(ans){
            cout << "YES" << endl;
        }else
            cout << "NO" << endl;
    }
}