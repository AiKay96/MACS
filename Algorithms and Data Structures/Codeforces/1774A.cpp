// https://codeforces.com/contest/1774/problem/A
// https://codeforces.com/problemset/problem/1774/A

#include <bits/stdc++.h>
using namespace std;
int t, n, a, b;
string s;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        cin >> s;
        int ans = s[0] - '0';
        string answer = "";
        for(int i = 1; i < n; i++){
            if(ans == 1){
                answer+="-";
                ans-= s[i] - '0';
            }else{
                answer+="+";
                ans+= s[i] - '0';
            }
        }
        cout << answer << endl;
    }
}