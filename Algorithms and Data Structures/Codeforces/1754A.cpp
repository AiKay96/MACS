// https://codeforces.com/contest/1754/problem/A
// https://codeforces.com/problemset/problem/1754/A

#include <bits/stdc++.h>
using namespace std;
int t, n;
string s;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        cin >> s;
        int numQ = 0;
        for(int i = 0; i < n; i++){
            if(s[i] != 'A'){
                numQ++;
            }else{
                if(numQ != 0){
                    numQ--;
                }
            }
        }
        if(numQ == 0){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
}