// https://codeforces.com/contest/1586/problem/C
// https://codeforces.com/problemset/problem/1586/C

#include<bits/stdc++.h>
using namespace std;
int n, m;
int main(){
    ios::sync_with_stdio(false);
    cin >> n >> m;
    bool arr[n][m];
    for(int i = 0; i < n; i++){
        string s;
        cin >> s;
        for(int j = 0; j < s.length(); j++){
            if(s[j] == '.')
                arr[i][j] = false;
            else
                arr[i][j] = true;
        }
    }
    vector<int> svetebi(m, 0);
    for(int i = 1; i < n; i++){
        for(int j = 1; j < m; j++){
            if(arr[i][j-1] && arr[i-1][j])
                svetebi[j] = 1;
        }
    }
    for(int i = 1; i < m; i++)
        svetebi[i] += svetebi[i-1];
    
    int q;
    cin >> q;
    for(int k = 0; k < q; k++){
        int a, b;
        cin >> a >> b;
        a--;
        b--;
        if(svetebi[b] - svetebi[a] == 0)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
    }
}