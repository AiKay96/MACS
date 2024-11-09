// https://codeforces.com/gym/105079/problem/D
// https://codeforces.com/problemset/gymProblem/105079/D

#include <bits/stdc++.h>
using namespace std;
long long arr[100001];

int main() {
    long long n, a, b;
    cin >> n >> a >> b;
    long long ans = 0;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    for (int i = 0; i < n; i++)
        arr[i] = a * arr[i] + b;
    sort(arr, arr + n);
    for (int i = 0; i < n; i++)
        ans += (i+1) * arr[i];
    cout << ans;
}