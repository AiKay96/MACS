// https://codeforces.com/contest/1766/problem/D
// https://codeforces.com/problemset/problem/1766/D

#include <bits/stdc++.h>
using namespace std;
int a, b, t, h, i, j, n, num[10000001];

int main(){
    std::ios::sync_with_stdio(false);
    for(i = 2; i <=3200; i++) {
        if (num[i] > 0) continue;
        else{
            for (j=i*i; j<=10000000; j=j+i)
                if (num[j]==0) num[j]=i;
        }
    }
    cin >> t;
    for(h = 0; h < t; h++){
        cin >> a >> b;
        n = abs(a-b);
        if(n == 1){
            cout << -1 << endl;
        }else if(__gcd(a, b) != 1){
            cout << 0 << endl;
        }else{
            int ans = INT_MAX;
            while (num[n]!=0) {
                ans = min(ans, abs(num[n] - a%num[n]));
                n=n/num[n];
            }
            ans = min(ans, abs(n - a%n));
            cout << ans << endl;
        }
    }
}