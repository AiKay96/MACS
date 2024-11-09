// https://codeforces.com/contest/505/problem/B
// https://codeforces.com/problemset/problem/505/B

#include<bits/stdc++.h>
using namespace std;
int dsu[101][101];
int findParent(int color, int curr){
    if(dsu[color][curr] == curr)
        return curr;
    return dsu[color][curr] = findParent(color, dsu[color][curr]);
}
 
int main() {
    ios_base::sync_with_stdio(false);
    for(int i = 1; i <= 100; i++)
        for(int j = 1; j <= 100; j++)
            dsu[i][j] = j;
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b, c;
        cin >> a >> b >> c;
        int aParent = findParent(c, a);
        int bParent = findParent(c, b);
        dsu[c][aParent] = bParent;
    }
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int  u, v;
        cin >> u >> v;
        int ans = 0;
        for(int j = 1; j <= 100; j++)
            if(findParent(j, u) == findParent(j, v))
                ans++;
        cout << ans << endl;
    }
}