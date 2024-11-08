// https://codeforces.com/contest/1742/problem/D
// https://codeforces.com/problemset/problem/1742/D

#include <bits/stdc++.h>
using namespace std;
int t, n, a;
int arr[1001];
int main(){
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        for(int i = 0; i < n; i++){
            cin >> a;
            arr[a] = i+1;
        }
        int ans = -1;
        for(int i = 0; i < 1001; i++){
            for(int j = i; j < 1001; j++){
                if(arr[i] != 0 && arr[j] && __gcd(i, j) == 1)
                    ans = max(ans, arr[i]+arr[j]);
            }
        }
        for(int i = 0; i < 1001; i++)
            arr[i] = 0;
        cout << ans << endl;
    }
}