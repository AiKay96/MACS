// https://codeforces.com/contest/1304/problem/E
// https://codeforces.com/problemset/problem/1304/E

#include "bits/stdc++.h"
using namespace std;

vector<int> graph[200005];
int par[200005][20], d[200005], incount[200005], outcount[200005], t;

bool check(int x, int k){
    if(x > k || (x & 1) != (k & 1))
        return false;
    return true;
}
void dfs(int u, int p){
    t++;
    incount[u] = t;
    for(int k = 1; k < 20; k++)
        par[u][k] = par[par[u][k-1]][k-1];
    for(int i = 0; i < graph[u].size(); i++){
        int v = graph[u][i];
        if(v != p){
           d[v] = d[u] + 1;
           par[v][0] = u;
           dfs(v, u);
        }
    }
    t++;
    outcount[u] = t;
}
int LCA(int u, int v){
    if(d[u] > d[v])
        swap(u,v);
    int dist = d[v] - d[u];
    for(int i = 0; i < 20; i++)
        if(dist >> i & 1)
            v = par[v][i];
    if(u == v)
        return u;
    for(int i = 19; i >= 0; i--)
        if(par[u][i] != par[v][i]){
          u = par[u][i];
          v = par[v][i];
        }
    return par[u][0];
}
int distance(int x, int y){
    return d[x] + d[y] - 2 * d[LCA(x,y)];
}
int main(){
    ios_base::sync_with_stdio(0);
    int n;
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    dfs(1, 1);
    int q; 
    cin >> q;
    for(int i = 0; i < q; i++){
        int x, y, u, v, k;
        cin >> x >> y >> u >> v >> k;
        if(check(distance(u,v), k))
          cout<< "YES" << endl;
        else if(check(distance(u,x) + 1 + distance(y,v), k))
          cout<< "YES" << endl;
        else if(check(distance(v,x) + 1 + distance(y,u), k))
          cout<< "YES" << endl;
        else
            cout<<"NO" << endl;;
    }
}