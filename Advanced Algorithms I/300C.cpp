// https://codeforces.com/contest/300/problem/C
// https://codeforces.com/problemset/problem/300/C

#include<bits/stdc++.h>
using namespace std;
#define int long long
long long p = 1000000007;
int f[1000001], invf[1000001];
int fastPow(int x, int n){
    if(n == 0)
        return 1;
    if(n % 2 == 1)
        return (fastPow(x, n-1) * x) % p;
    int nax = fastPow(x, n/2);
    return (nax * nax) % p;
}
bool good(int a, int b, int num){
    if(num == 0)
        return true;
    if(num % 10 == a || num % 10 == b)
        return good(a, b, num/10);
    return false;
}

main() {
    ios_base::sync_with_stdio(false);
    int a, b, n;
    cin >> a >> b >> n;
    f[0] = 1;
    for(int i = 1; i <= n; i++)
        f[i] = (f[i-1] * i) % p;
    invf[0] = 1;
    for(int i = 1; i <= n; i++)
        invf[i] = fastPow(f[i], p-2);
    int ans = 0;
    for(int i = 0; i <= n; i++){
        int sum = i * a + (n-i) * b;
        if(good(a, b, sum))
            ans = (ans + (((f[n] * invf[n-i]) % p) * invf[i]) % p) % p;
    }
    cout << ans << endl;
}