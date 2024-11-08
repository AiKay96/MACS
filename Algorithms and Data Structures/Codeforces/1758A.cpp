// https://codeforces.com/contest/1758/problem/A
// https://codeforces.com/problemset/problem/1758/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    string s;
    for(int i = 0; i < n; i++){
        cin >> s;
        int len = s.length();
        for(int j = len - 1; j >= 0; j--){
            s+= s[j];
        }
        cout << s << endl;
    }
}