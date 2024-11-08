// https://codeforces.com/contest/576/problem/C
// https://codeforces.com/problemset/problem/576/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, k;
    cin >> n >> k;
    long long arr[n];
    map<long long, long long> left;
    map<long long, long long> right;
    long long ans = 0;
    for(int i = 0; i < n; i++){
        cin >> arr[i];
        right[arr[i]]++;
        left[arr[i]] = 0;
    }
    left[arr[0]]++;
    right[arr[0]]--;
    for(int i = 1; i < n - 1; i++){
        int mid = arr[i];
        right[mid]--;
        if(mid%k != 0){
            left[mid]++;
            continue;
        }
        ans += (long long)(left[mid/k]*right[(long long)mid*k]);
        left[mid]++;
    }
    cout << ans << endl;
}