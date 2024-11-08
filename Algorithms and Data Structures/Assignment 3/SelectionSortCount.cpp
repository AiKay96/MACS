// https://vjudge.net/contest/522920#problem/C

#include <bits/stdc++.h>
using namespace std;

long long factorial[200001];
int prime, Swap[200000], n;
long long powN(int n, long long x);
long long C(long long n, long long m);
long long ans;
void recursion(int i);

int main(){
    prime = 998244353;
	cin >> n;
	for(int i = 0; i < n - 1; i++)
	    cin >> Swap[i+1];
    factorial[0] = 1;
    for(int i = 1; i <= n; i++){
        factorial[i] = (factorial[i-1]*i)%prime;
    }
    ans = 1;
    recursion(n - 2);
    cout << ans << endl;
}
void recursion(int i){
    if(i == 0)
        return;
    ans *= C(Swap[i+1] + 1, Swap[i]);
    ans %= prime;
    recursion(i-1);
}
long long powN(int n, long long x){
    if(n == 0)
        return 1;
    if(n % 2 == 0){
        long long a = powN(n/2, x);
        return (a*a) % prime;
    }else{
        long long a = powN(n-1, x);
        return (a*x) % prime;
    }
}
long long C(long long n, long long m){
    long long ans = (long long)(factorial[n] * powN(prime - 2, factorial[m]))%prime;
    ans = (long long)(ans * powN(prime - 2, factorial[n - m]))%prime;
    return ans;
}
