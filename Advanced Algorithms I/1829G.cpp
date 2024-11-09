// https://codeforces.com/contest/1829/problem/G
// https://codeforces.com/problemset/problem/1829/G

#include<bits/stdc++.h>
using namespace std;
long long dp[2100000];
long long quaso(long long x){
    return x*x;
}
void filldp(){
    dp[0] = 0;
    dp[1] = 1;
    for(long long lvl = 2; lvl < 2023; lvl++){
        long long num = (lvl - 1) * lvl;
        num /= 2;
        for(long long i = 1; i <= lvl; i++){
            long long ans = quaso(num + i);
            //marcxniv
            if(i > 1)
                ans += dp[num - lvl + i];
            //marjvniv
            if(i < lvl)
                ans += dp[num - lvl + i + 1];
            if(i > 1 && i < lvl){
                long long ind = (lvl - 3) * (lvl - 2);
                ind /= 2;
                ans -= dp[ind + i - 1];
            }
            dp[num + i] = ans;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    filldp();
    int t;
    cin >> t;
    for(int p = 0; p < t; p++){
        int n;
        cin >> n;
        cout << dp[n] << endl;
    }
}