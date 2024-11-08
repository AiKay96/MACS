// https://codeforces.com/contest/1737/problem/B
// https://codeforces.com/problemset/problem/1737/B

#include <bits/stdc++.h>
using namespace std;
int t;
long long l, r, ansL, ansR;
long long calculate(long long n){
    if(n == 0)
        return n;
    long long num = sqrt(n);
    long long ans = num + (num - 1) * 2;
    long long full = num * num;
    full += num;
    if(full <= n)
        ans++;
    full += num;
    if(full <= n)
        ans++;
    //cout << n << " " <<  ans << endl;
    return ans;
}
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> l >> r;
        ansL = calculate(l-1);
        ansR = calculate(r);
        cout << ansR - ansL << endl;
    }
}