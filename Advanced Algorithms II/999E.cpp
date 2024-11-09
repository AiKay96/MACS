// https://codeforces.com/contest/999/problem/E
// https://codeforces.com/problemset/problem/999/E

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5010;
vector<int> g[MAXN];
bool used[MAXN];
bool good[MAXN];
int cnt;

void dfs1(int v) {
    good[v] = true;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (!good[to])
            dfs1(to);
    }
}

void dfs2(int v) {
    used[v] = true;
    cnt++;
    for (int i = 0; i < g[v].size(); i++) {
        int to = g[v][i];
        if (!used[to] && !good[to])
            dfs2(to);
    }
}

int main() {
    int n, m, s;
    cin >> n >> m >> s;
    s--;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--;
        y--;
        g[x].push_back(y);
    }
    dfs1(s);
    vector<pair<int, int>> vertices;
    for (int i = 0; i < n; i++) {
        if (!good[i]) {
            cnt = 0;
            memset(used, false, sizeof(used));
            dfs2(i);
            vertices.push_back({cnt, i});
        }
    }
    sort(vertices.begin(), vertices.end(), greater<pair<int, int>>());
    int ans = 0;
    for (int i = 0; i < vertices.size(); i++) {
        int v = vertices[i].second;
        if (!good[v]) {
            ans++;
            dfs1(v);
        }
    }
    cout << ans << endl;
}