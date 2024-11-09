// https://codeforces.com/contest/11/problem/D
// https://codeforces.com/problemset/problem/11/D

#include "bits/stdc++.h"
using namespace std;

bool arr[20][20];
long long dp[1<<20][20];
 
int main(){
    int n, m, a;
    long long ans = 0;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        if(x > y)
            swap(x, y);
        arr[x][y] = true;
        arr[y][x] = true;
        dp[(1 << x) + (1 << y)][y] = 1;
    }
    for(int i = 7; i < (1 << n); i++){
        bool flag = true;
        for(int j = 0; j < n; j++){
            if(i & (1 << j) && dp[i][j] == 0){
                if(flag){
                    flag = false;
                    a = j;
                }else{
                    for(int k = a + 1; k < n; k++)
                        if(i & (1 << k) && arr[j][k])
                            dp[i][j] += dp[i - (1 << j)][k];
                    if(arr[a][j])
                        ans += dp[i][j];
                }
            }
        }
    }
    cout << ans / 2 << endl;
}