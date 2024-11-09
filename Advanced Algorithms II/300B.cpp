// https://codeforces.com/contest/300/problem/B
// https://codeforces.com/problemset/problem/300/B

#include <bits/stdc++.h>
using namespace std;

int n, m, u, v;
int adj[52][52], used[52], deg[52];
pair<int, int> ord[52];
vector<int> grp;
vector<vector<int>> result;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u >> v;
        u--;
        v--;
        deg[u]++;
        deg[v]++;
        adj[u][v] = 1;
        adj[v][u] = 1;
    }

    for (int i = 0; i < n; i++) {
        if (deg[i] > 2){
            cout << "-1" << endl;
            return 0;
        }
        ord[i] = make_pair(deg[i], i);
    }

    sort(ord, ord + n, greater<pair<int, int>>());

    result.clear();

    for (int i = 0; i < n; i++) {
        int u = ord[i].second;
        if (used[u])
            continue;
        grp.clear();
        grp.push_back(u);
        used[u] = 1;

        for (int j = 0; j < n; j++) {
            if (!adj[u][j])
                continue;
            if (used[j]){
                cout << "-1" << endl;
                return 0;
            }
            grp.push_back(j);
            used[j] = 1;
        }

        if (grp.size() > 3){
            cout << "-1" << endl;
            return 0;
        }
        while (grp.size() < 3) {
            bool found = false;
            for (int j = 0; j < n; j++) {
                if (used[j] || deg[j]) continue;
                grp.push_back(j);
                used[j] = 1;
                found = true;
                break;
            }
            if (!found){
                cout << "-1" << endl;
                return 0;
            }
        }

        sort(grp.begin(), grp.end());
        result.push_back(grp);
    }

    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < 3; j++)
            cout << result[i][j] + 1 << " ";
        cout << endl;
    }

    return 0;
}