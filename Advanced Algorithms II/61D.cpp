// https://codeforces.com/contest/61/problem/D
// https://codeforces.com/problemset/problem/61/D

#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> graph[100001];
long long dist[100001];
bool visited[100001];
queue<int> q;

int main(void) {
    int n, x, y, w;
    long long all = 0;
    
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> x >> y >> w;
        x--; 
        y--;
        graph[x].push_back({y, w});
        graph[y].push_back({x, w});
        all += 2 * w;
    }
    
    dist[0] = 0;
    q.push(0);
    
    while (!q.empty()) {
        x = q.front(); 
        visited[x] = true;
        q.pop();
        
        for (int i = 0; i < graph[x].size(); i++) {
            y = graph[x][i].first;
            if (!visited[y]) {
                dist[y] = dist[x] + graph[x][i].second;
                q.push(y);
            }
        }
    }
    
    long long biggest = 0;
    for (int i = 0; i < n; i++) 
        biggest = max(biggest, dist[i]);

    cout << all - biggest << endl;
}