// https://codeforces.com/contest/1717/problem/D
// https://codeforces.com/problemset/problem/1717/D

#include <bits/stdc++.h>
using namespace std;
long long factorial[100001];
long long powN(int n, long long x);
long long C(long long n, long long m);
int main(){
    int n, k;
	cin >> n >> k;
    int num = powN(n, 2);
    if(k >= n){
        cout << num << endl;
        return 0;
    }
    k = n - k;
    factorial[0] = 1;
    for(int i = 1; i <= n; i++){
        factorial[i] = (factorial[i-1]*i)%1000000007;
    }
    long long ans = powN(n, 2);
    for(int i = 0; i < k; i++){
        ans -= C(n, i);
        if(ans < 0)
            ans += 1000000007;
    }
    cout << ans << endl;
}
long long powN(int n, long long x){
    if(n == 0)
        return 1;
    if(n % 2 == 0){
        long long a = powN(n/2, x);
        return (a*a) % 1000000007;
    }else{
        long long a = powN(n-1, x);
        return (a*x) % 1000000007;
    }
}
long long C(long long n, long long m){
    long long ans = (long long)(factorial[n] * powN(1000000005, factorial[m]))%1000000007;
    ans = (long long)(ans * powN(1000000005, factorial[n - m]))%1000000007;
    return ans;
}