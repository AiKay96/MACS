// https://codeforces.com/gym/105079/problem/E
// https://codeforces.com/problemset/gymProblem/105079/E

#include <bits/stdc++.h>
using namespace std;
int arr[1001][1001], dp[1001][1001];
int n;
int dfs (int x, int y){
    if(x >= n || y >= n || arr[x][y] == -1)
        return INT_MIN;
    if (x == n-1 && y == n-1)
        return arr[x][y];
    if (dp[x][y] != -1)
        return dp[x][y];
    
    int right = dfs(x+1, y);
    int down = dfs(x, y+1);
    dp[x][y] = arr[x][y] + max(right, down);
    
    return dp[x][y];
}
int main() {
    cin >> n;
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cin >> arr[i][j];
            dp[i][j] = -1;
        }
    }
    int ans = dfs(0, 0);
    if(ans < 0)
        cout << -1;
    else
        cout << ans;
}