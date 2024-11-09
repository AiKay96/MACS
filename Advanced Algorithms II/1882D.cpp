// https://codeforces.com/contest/1882/problem/D
// https://codeforces.com/problemset/problem/1882/D

#include <bits/stdc++.h>
using namespace std;

const int maxn = 500001;
vector<int> graph[maxn];
int val[maxn];
long long dp[maxn];
int n, sz[maxn];

void dfs_up(int node, int par) {
    dp[node] = 0;
    sz[node] = 1;
    for (int i = 0; i < graph[node].size(); i++) {
        int curr = graph[node][i];
        if (curr != par) {
            dfs_up(curr, node);
            sz[node] += sz[curr];
            long long w = val[curr] ^ val[node];
            dp[node] += dp[curr] + w * sz[curr];
        }
    }
}

void dfs_down(int node, int par) {
    for (int i = 0; i < graph[node].size(); i++) {
        int curr = graph[node][i];
        if (curr != par) {
            long long w = val[curr] ^ val[node];
            long long delta = dp[node] - (dp[curr] + w * sz[curr]);
            dp[curr] += delta + w * (n - sz[curr]);
            dfs_down(curr, node);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    for (int k = 0; k < t; k++) {
        cin >> n;
        for (int i = 1; i <= n; i++) {
            graph[i].clear();
            cin >> val[i];
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        dfs_up(1, 0);
        dfs_down(1, 0);
        for (int i = 1; i <= n; i++) 
            cout << dp[i] << " ";
        cout << endl;
    }
}