// https://codeforces.com/contest/911/problem/F
// https://codeforces.com/problemset/problem/911/F

#include<bits/stdc++.h>
using namespace std;

vector<int> graph[200001];
int maxu, furthest, root; 
int parent[200001], depth[200001], visited[200001];
long long weight = 0;
vector<pair<int, int> > ans;


void dfs1(int node, int parentu) {
    parent[node] = parentu;
    depth[node] = depth[parentu] + 1;
    
    if (depth[node] > maxu) {
        maxu = depth[node];
        furthest = node;
    }
    
    for (int i = 0; i < graph[node].size(); i++)
        if (graph[node][i] != parentu)
            dfs1(graph[node][i], node);
}

void dfs2(int node, int dist, int first, bool is_fl = false) {
    visited[node] = 1;

    for (int i = 0; i < graph[node].size(); i++) 
        if (!visited[graph[node][i]])
            dfs2(graph[node][i], dist + 1, first, true);

    if (is_fl) {
        weight += dist;
        ans.push_back({first, node});
    }
}

int main() {
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int x, y;
        cin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    maxu = 0;
    dfs1(1, 0);

    maxu = 0;
    root = furthest;
    dfs1(root, 0);

    weight = (long long)maxu * (maxu - 1) / 2;

    int curr = furthest;
    while (curr) {
        visited[curr] = 1;
        curr = parent[curr];
    }

    curr = furthest;
    while(curr) {
        if (depth[curr] - 1 > depth[furthest] - depth[curr])
            dfs2(curr, depth[curr] - 1, root);
        else
            dfs2(curr, depth[furthest] - depth[curr], furthest);
        curr = parent[curr];
    }

    cout << weight << endl;

    for (int i = 0; i < ans.size(); i++) 
        cout << ans[i].first << " " << ans[i].second << " " << ans[i].second << endl;

    curr = furthest;
    while (curr != root) {
        cout << root << " " << curr << " " << curr << endl;
        curr = parent[curr];
    }
}