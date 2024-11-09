// https://codeforces.com/contest/471/problem/D
// https://codeforces.com/problemset/problem/471/D

#include <bits/stdc++.h>
using namespace std;

vector<int> zFuncion(vector<int> &str) {
    int l = 0, r = 0, n = str.size();
    vector<int> v(n + 3);
    for (int i = 1; i < n; i ++) {
        if (i < r) {
            v[i] = min (r - i, v[i - l]);
        }

        while (i + v[i] < n && str[v[i]] == str[i + v[i]]) {
            v[i] ++;
        }

        if (i + v[i] > r) {
            r = i + v[i];
            l = i;
        }
    }
    return v;
}
int main() {
    int n, m;
    cin >> n;
    cin >> m;
    vector<int> a, b;
    for(int i = 0; i < n; i++){
        int t;
        cin >> t;
        a.push_back(t);
    }
    for(int i = 0; i < m; i++){
        int t;
        cin >> t;
        b.push_back(t);
    }
    for (int i = 0 ; i < a.size() - 1; i++)
        a[i] = a[i + 1] - a[i];
    for (int i = 0 ; i < b.size() - 1; i++)
        b[i] = b[i + 1] - b[i];
    a.erase(a.end() - 1);
    b.erase(b.end() - 1);
    
    int sz = b.size();
    if(sz == 0){
        cout << a.size() + 1 << endl;
        return 0;
    }
    vector<int> str = b;
    for(int i = 0; i < a.size(); i++)
        str.push_back(a[i]);
    vector<int> zFunc = zFuncion(str);
 
    int res = 0;
    for (int i = sz ; i < zFunc.size() ; i++) 
        if (zFunc[i] >= sz) 
            res++;
    cout << res << endl;
}