// https://codeforces.com/contest/1774/problem/C
// https://codeforces.com/problemset/problem/1774/C

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, ans[200001];
string s;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        cin >> s;
        for(int i = 0; i < 200001; i++){
            ans[i] = 0;
        }
        ans[0] = 1;
        int countZero = 0;
        int countOne = 0;
        bool prevIsZero;
        if(s[0] == '0'){
            prevIsZero = true;
            countZero++;
        }else{
            prevIsZero = false;
            countOne++;
        }
        for(int i = 1; i < n-1; i++){
            int num = i+2;
            if(s[i] == '0'){
                if(prevIsZero){
                    countZero++;
                }else{
                    prevIsZero = true;
                    countZero = 1;
                }
                ans[i] = num - countZero;
            }else{
                if(!prevIsZero){
                    countOne++;
                }else{
                    prevIsZero = false;
                    countOne = 1;
                }
                ans[i] = num - countOne;
            }
        }
        for(int i = 0; i < n-1; i++){
            cout << ans[i] << " ";
        }
        cout << endl;
    }
}