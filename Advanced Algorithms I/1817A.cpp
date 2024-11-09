// https://codeforces.com/contest/1817/problem/A
// https://codeforces.com/problemset/problem/1817/A

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;
    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    int pref[n];
    pref[0] = 0;
    for(int i = 1; i < n-1; i++){
        pref[i] = pref[i-1];
        if(arr[i-1] >= arr[i] && arr[i] >= arr[i+1])
            pref[i]++;
    }
    pref[n-1] = pref[n-2];
    for(int i = 0; i < q; i++){
        int l, r;
        cin >> l >> r;
        if(l == r)
            cout << 1 << endl;
        else{
            l--;
            r--;
            cout << r - l + 1 - pref[r-1] + pref[l] << endl;
        }
    }
}