// https://codeforces.com/gym/102911/problem/B1
// https://codeforces.com/problemset/gymProblem/102911/B1

#include <bits/stdc++.h>
using namespace std;
long long arr[61], pow2[61];
int main(){
    int n, k;
    cin >> n >> k;
    pow2[0] = 1;
    for(int i = 1; i <= 60; i++)
        pow2[i] = 2 * pow2[i-1];
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        arr[a]++;
    }
    long long ans = 1;
    for(int i = 1; i <= k; i++)
        ans *= pow2[arr[i]] - 1;
    cout << ans << endl;
}