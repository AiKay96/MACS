// https://codeforces.com/contest/570/problem/C
// https://codeforces.com/problemset/problem/570/C

#include<bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    s = 'k' + s + 'k';
    n += 2;
    int len = 0;
    int qnt = 0;
    bool started = false;
    for(int i = 0; i < n; i++){
        if(s[i] == '.'){
            len++;
            if(!started){
                qnt++;
                started = true;
            }
        }else
            started = false;
    }
    for(int i = 0; i < m; i++){
        int ind;
        char c;
        cin >> ind >> c;
        if(c == '.' && s[ind] != '.'){
            len++;
            if(s[ind-1] == '.' && s[ind+1] == '.')
                qnt--;
            else if(s[ind-1] != '.' && s[ind+1] != '.')
                qnt++;
        }
        if(c != '.' && s[ind] == '.'){
            len--;
            if(s[ind-1] == '.' && s[ind+1] == '.')
                qnt++;
            else if(s[ind-1] != '.' && s[ind+1] != '.')
                qnt--;
        }
        s[ind] = c;
        cout << len - qnt << endl;
    }
    
}