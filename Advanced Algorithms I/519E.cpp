// https://codeforces.com/contest/519/problem/E
// https://codeforces.com/problemset/problem/519/E

#include <bits/stdc++.h>
 
using namespace std;
 
vector <int> graph[100010];
int n, c, incount[100010], outcount[100010], d[100010], sz[100010], par[100010][30];

bool isPar(int a, int b) {
    return incount[a] <= incount[b] && outcount[b] <= outcount[a];
}
 
int findPar(int a, int b) {
    for (int i = 29; i >= 0; i--) 
        if (!isPar(par[a][i], b)) 
            a = par[a][i];
    return a;
}

void dfs(int v, int p, int k) {
    c++;
    par[v][0] = p;
    sz[v] = 1;
    d[v] = k;
    incount[v] = c;
    for (int i = 1; i < 30; i++) 
        par[v][i] = par[par[v][i - 1]][i - 1];
    for (int i = 0; i < graph[v].size(); i++) {
        int to = graph[v][i];
        if (to != p) {
            dfs(to, v, k + 1);
            sz[v] += sz[to];
        }
    }
    c++;
    outcount[v] = c;
}
 
int lca(int a, int b) {
    if (isPar(a, b)) 
        return a;
    if (isPar(b, a)) 
        return b;
    return par[findPar(a, b)][0];
}
 
int query(int a, int b) {
    if (a == b) 
        return n;
    int l = lca(a, b);
    int ans = -1;
    if (d[a] - d[l] == d[b] - d[l]) {
        a = findPar(a, l);
        b = findPar(b, l);
        return n - sz[a] - sz[b];
    }
    if (d[a] < d[b]) 
        swap(a, b);
    int to = a;
    int dist = d[a] + d[b] - 2 * d[l];
    if (dist % 2 == 1) 
        return 0;
    dist /= 2;
    for (int i = 29; i >= 0; i--) 
        if (d[a] - d[par[to][i]] < dist) 
            to = par[to][i];
    int mid = par[to][0];
    return sz[mid] - sz[to];
}
 
int main() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }
    dfs(1, 1, 0);
    int q;
    cin >> q;
    for(int i = 0; i < q; i++){
        int a, b;
        cin >> a >> b;
        cout << query(a, b) << endl;
    }
}