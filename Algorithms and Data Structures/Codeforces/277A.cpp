// https://codeforces.com/contest/277/problem/A
// https://codeforces.com/problemset/problem/277/A

#include <bits/stdc++.h>
using namespace std;

int n, m, dsu[201], usedLang[201];
int findParent(int i){
    if(dsu[i] == i)
        return i;
    else return dsu[i] = findParent(dsu[i]);
}
int main(){
    cin >> n >> m;
    for(int i = 0; i <= m+ n; i++)
        dsu[i] = i;
    for(int i = 1; i <= n; i++){
        int numLang;
        cin >> numLang;
        for(int j = 0; j < numLang; j++){
            int lang;
            cin >> lang;
            usedLang[n+lang] = 1;
            dsu[findParent(i)] = findParent(dsu[n+lang]);
        }
    }
    for(int i = 1; i <= m+n; i++)
        dsu[i] = findParent(dsu[i]);
    for(int i = 1; i <= m+ n; i++)
        usedLang[dsu[i]]++;
    int ans = 0;
    bool dunnoLang = true;
    for(int i = 1; i <= m+ n; i++){
        if(dsu[i] <= n || usedLang[i] > 1)
            ans++;
        if(dunnoLang && usedLang[i] > 1)
            dunnoLang = false;
    }
    if(!dunnoLang)
        ans--;
    cout << ans << endl;
}