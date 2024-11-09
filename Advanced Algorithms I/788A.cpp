// https://codeforces.com/contest/788/problem/A
// https://codeforces.com/problemset/problem/788/A

#include <bits/stdc++.h>
using namespace std;
int main() {
    long long n;
    cin >> n;
    long long arr[n+1];
    for (int i = 1; i <= n; i++) 
    	cin >> arr[i];
    long long diff[n];
    for (int i = 1; i < n; i++) 
    	diff[i] = (long long) abs(arr[i + 1] - arr[i]);
    long long even[n], odd[n];
    for(int i = 0; i < n; i++){
        even[i] = 0;
        odd[i] = 0;
    }
    long long ans = 0;
    for (int i = 1; i < n; i++) {
    	even[i] = odd[i - 1] + diff[i];
    	odd[i] = (long long) max(even[i - 1] - diff[i], (long long)0);
    	ans = max(ans, (long long)max(even[i], odd[i]));
    }
    cout << ans;
}