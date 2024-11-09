// https://codeforces.com/contest/372/problem/B
// https://codeforces.com/problemset/problem/372/B

#include <bits/stdc++.h>
using namespace std;
int arr[1001][1001], ertebi[1001][1001], dp[50][50][50][50];
int n, m, q, a, b, c, d;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            char a;
            cin >> a;
            if(a == '1')
                arr[i][j] = 1;
            else
                arr[i][j] = 0;
        }
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            ertebi[i][j] = ertebi[i-1][j] + ertebi[i][j-1] - ertebi[i-1][j-1] + arr[i][j];
    
    //dp[a][b][c][d] = number of rectangles, that ends on (c, d)
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            for(int k = i; k > 0; k--){
                for(int t = j; t > 0; t--){
                    dp[k][t][i][j] = dp[k+1][t][i][j] + dp[k][t+1][i][j] - dp[k+1][t+1][i][j];
                    if(ertebi[i][j] + ertebi[k-1][t-1] == ertebi[i][t-1] + ertebi[k-1][j])
                        dp[k][t][i][j]++;
                    
                }
            }
        }
    }
    //dp[a][b][c][d] = number of rectangles in range (a, b), (c, d)
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m; j++)
            for(int k = i; k <= n; k++)
                for(int t = j; t <= m; t++)
                    dp[i][j][k][t] += dp[i][j][k-1][t] + dp[i][j][k][t-1] - dp[i][j][k-1][t-1];
    for(int i = 0; i < q; i++){
        cin >> a >> b >> c >> d;
        cout << dp[a][b][c][d] << endl;
    }
 
}