// https://codeforces.com/contest/1722/problem/E
// https://codeforces.com/problemset/problem/1722/E

#include <bits/stdc++.h>
using namespace std;
long long dp[1001][1001];
int main(){
    int t;
    cin >> t;
    for(int r = 0; r < t; r++){
        int n, q;
        cin >> n >> q;
        map<pair<int, int>, int > mp;
        for(int i = 0; i < n; i++){
            int h, w;
            cin >> h >> w;
            mp[{h,w}]++;
        }
        for(int i = 2; i < 1001; i++){
            for(int j = 2; j < 1001; j++){
                dp[i][j] = dp[i][j-1] + dp[i-1][j] - dp[i-1][j-1];
                if(mp.count({i-1, j-1}))
                    dp[i][j] += (long long)mp[{i-1,j-1}]*(i-1)*(j-1);

            }
        }
        for(int l = 0; l < q; l++){
            int hs, ws, hb, wb;
            cin >> hs >> ws >> hb >> wb;
            cout << dp[hb][wb] - dp[hs+1][wb] - dp[hb][ws+1] + dp[hs+1][ws+1] << endl;
        }
    }
}