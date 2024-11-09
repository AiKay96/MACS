// https://codeforces.com/contest/1051/problem/D
// https://codeforces.com/problemset/problem/1051/D

#include<bits/stdc++.h>
using namespace std;
#define int long long
int p = 998244353;

int main(){
  	ios_base::sync_with_stdio(false);
    int n, k;
    cin >> n >> k;
    int ww[n+1][k+1], wb[n+1][k+1], bw[n+1][k+1], bb[n+1][k+1];
    for(int i = 0; i <= n; i++){
        for(int j = 0; j <= k; j++){
                ww[i][j] = 0;
                wb[i][j] = 0;
                bw[i][j] = 0;
                bb[i][j] = 0;
        }
    }
    ww[1][1] = 1;
    wb[1][2] = 1;
    bw[1][2] = 1;
    bb[1][1] = 1;
    for(int i = 2; i <= n; i++){
        for(int j = 1; j <= k; j++){
            ww[i][j] = (ww[i][j] + ww[i-1][j]) % p;
            if(j > 0)
                ww[i][j] = (ww[i][j] + bb[i-1][j-1]) % p;
            ww[i][j] = (ww[i][j] + wb[i-1][j]) % p;
            ww[i][j] = (ww[i][j] + bw[i-1][j]) % p;
            
            bb[i][j] = (bb[i][j] + bb[i-1][j]) % p;
            if(j > 0)
                bb[i][j] = (bb[i][j] + ww[i-1][j-1]) % p;
            bb[i][j] = (bb[i][j] + wb[i-1][j]) % p;
            bb[i][j] = (bb[i][j] + bw[i-1][j]) % p;
            
            if(j > 0)
                wb[i][j] = (wb[i][j] + ww[i-1][j-1]) % p;
            if(j > 0)
                wb[i][j] = (wb[i][j] + bb[i-1][j-1]) % p;
            if(j > 1)
                wb[i][j] = (wb[i][j] + bw[i-1][j-2]) % p;
            wb[i][j] = (wb[i][j] + wb[i-1][j]) % p;
            
            if(j > 0)
                bw[i][j] = (bw[i][j] + ww[i-1][j-1]) % p;
            if(j > 0)
                bw[i][j] = (bw[i][j] + bb[i-1][j-1]) % p;
            if(j > 1)
                bw[i][j] = (bw[i][j] + wb[i-1][j-2]) % p;
            bw[i][j] = (bw[i][j] + bw[i-1][j]) % p;
        }
    }
    int ans = 0;
    ans = (ans + ww[n][k]) % p;
    ans = (ans + wb[n][k]) % p;
    ans = (ans + bw[n][k]) % p;
    ans = (ans + bb[n][k]) % p;
    cout << ans << endl;
}