// https://codeforces.com/contest/1743/problem/A
// https://codeforces.com/problemset/problem/1743/A

#include <bits/stdc++.h>
using namespace std;

int factorial[11];
int c (int n, int m){
    return factorial[n] / (factorial[m] * factorial[n-m]);
}
int main(){
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        factorial[0] = 1;
        for(int i = 1; i < 11; i++)
            factorial[i] = factorial[i-1]*i;
        int n;
        cin >> n;
        int arr[n];
        for(int i = 0; i < n; i++)
            cin >> arr[i];
        int ans = c(10-n, 2) * 6;
        cout << ans << endl;
    }
}