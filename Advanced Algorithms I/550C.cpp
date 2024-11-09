// https://codeforces.com/contest/550/problem/C
// https://codeforces.com/problemset/problem/550/C

#include<bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    string s;
    cin >> s;
    string dp[8][s.length()];
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < s.length(); j++)
            dp[i][j] = "";
    dp[(s[0] - '0')%8][0] = s[0];
    for(int i = 1; i < s.length(); i++){
        for(int j = 0; j < 8; j++){
            dp[j][i] = dp[j][i-1];
        }
        dp[(s[i] - '0')%8][i] = s[i];
        for(int j = 0; j < 8; j++){
            if(dp[j][i-1] != ""){
                dp[((10*j) + s[i] - '0') % 8][i] = dp[j][i-1];
                dp[((10*j) + s[i] - '0') % 8][i] += s[i];
            }
        }
    }
    string ans = dp[0][s.length() - 1];
    if(ans == ""){
        cout << "NO" << endl;
    }else{
        cout << "YES" << endl;
        cout << ans << endl;
    }
}