// https://codeforces.com/contest/835/problem/C
// https://codeforces.com/problemset/problem/835/C

#include <bits/stdc++.h>
using namespace std;

int dp[101][101][11];
 
int main(){
    int n, q, c;
    cin >> n >> q >> c;
    for(int i = 0; i < n; i++){
        int x, y, k;
        cin >>  x >> y >> k;
        dp[x][y][k]++;
    }
    for(int k = 0; k <= c; k++)
        for(int i = 1; i <= 100; i++)
            for(int j = 1; j <= 100; j++)
                dp[i][j][k] += dp[i-1][j][k] + dp[i][j-1][k] - dp[i-1][j-1][k];

    for(int i = 0; i < q; i++){
        int t, x1, x2, y1, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        int ans = 0;
        for(int k = 0; k <= c; k++){
            int br = (k + t) % (c + 1);
            ans += br * (dp[x2][y2][k] - dp[x1 - 1][y2][k] - dp[x2][y1 - 1][k] + dp[x1 - 1][y1 - 1][k]);
        }
        cout << ans << endl;
    }
}