// https://codeforces.com/contest/1766/problem/C
// https://codeforces.com/problemset/problem/1766/C

#include <bits/stdc++.h>
using namespace std;
int t, n;
bool dp[2][200001];
char wall[2][200001];
int main(){
    cin >> t;
    for(int h = 0; h < t; h++){
        for(int i = 0; i < 2; i++)
            for(int j = 0; j <= 20000; j++)
                wall[i][j] = '.';
        for(int i = 0; i < 2; i++)
            for(int j = 0; j <= 20000; j++)
                dp[i][j] = false;
        cin >> n;
        for(int i = 0; i < 2; i++)
            for(int j = 0; j < n; j++)
                cin >> wall[i][j];
        if(wall[0][0] == 'B')
            dp[0][0] = true;
        if(wall[1][0] == 'B')
            dp[1][0] = true;
        for(int j = 1; j < n; j++){
            if(wall[0][j] == 'B')
                dp[0][j] = (dp[0][j-1] && wall[1][j] != 'B') || (dp[1][j-1] && wall[1][j] == 'B');
            if(wall[1][j] == 'B')
                dp[1][j] = (dp[1][j-1] && wall[0][j] != 'B') || (dp[0][j-1] && wall[0][j] == 'B');
        }
        bool ans = dp[0][n-1] || dp[1][n-1];
        if(ans)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}