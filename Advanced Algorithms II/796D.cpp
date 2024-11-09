// https://codeforces.com/contest/796/problem/D
// https://codeforces.com/problemset/problem/796/D

#include <bits/stdc++.h>
using namespace std;

bool isSpecial[300005], visited[300005];
set<pair<int, int>> graph[300005];
bool result[300005];

int main() {
    int n, k, d;
    cin >> n >> k >> d;
    
    for (int i = 1; i <= k; i++) {
        int t;
        cin >> t;
        isSpecial[t] = true;
    }
    
    for (int i = 1; i < n; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].insert({b, i});
        graph[b].insert({a, i});
    }
    
    queue<pair<int, pair<int, int>>> que;
    for (int i = 1; i <= n; i++) {
        if (isSpecial[i]) {
            visited[i] = true;
            que.push({i, {-1, 0}});
        }
    }
    
    while (!que.empty()) {
        int curr = que.front().first;
        int par = que.front().second.first;
        int depth = que.front().second.second;
        que.pop();
        
        for (auto itr = graph[curr].begin(); itr != graph[curr].end();) {
            auto next = *itr;
            if (next.first == par) {
                itr++;
                continue;
            }
            if (visited[next.first] || depth == d) {
                result[next.second] = true;
                itr = graph[curr].erase(itr);
                graph[next.first].erase({curr, next.second});
            } else {
                visited[next.first] = true;
                que.push({next.first, {curr, depth + 1}});
                itr++;
            }
        }
    }
    
    int total = 0;
    for (int i = 1; i < n; i++) 
        total += result[i];
    cout << total << endl;
    
    for (int i = 1; i < n; i++) 
        if (result[i])
            cout << i << " ";
    cout << endl;
}