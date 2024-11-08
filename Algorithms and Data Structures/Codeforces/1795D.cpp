// https://codeforces.com/contest/1795/problem/D
// https://codeforces.com/problemset/problem/1795/D

#include <bits/stdc++.h>
using namespace std;
long long factorial[300001];
long long p = 998244353;
long long powN(int n, long long x){
    if(n == 0)
        return 1;
    if(n % 2 == 0){
        long long a = powN(n/2, x);
        return (a*a) % p;
    }else{
        long long a = powN(n-1, x);
        return (a*x) % p;
    }
}
long long C(long long n, long long m){
    long long ans = (long long)(factorial[n] * powN(p - 2, factorial[m]))%p;
    ans = (long long)(ans * powN(p - 2, factorial[n - m]))%p;
    return ans;
}
long long count(long long a, long long b, long long c){
    long long mini = min(a, min(b, c));
    long long counter = 0;
    if(mini == a)
        counter++;
    if(mini == b)
        counter++;
    if(mini == c)
        counter++;
    return counter;
}
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    factorial[0] = 1;
    for(int i = 1; i <= n; i++)
        factorial[i] = (factorial[i-1]*i)%p;
    long long arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    long long ans = 1;;
    for(int i = 2; i < n; i+=3)
        ans = (ans * count(arr[i], arr[i-1], arr[i-2]))%p;
    int zemota = n / 6;
    int qvemota = n / 3;
    ans = (ans * C(qvemota, zemota))%p;
    cout << ans << endl;
}