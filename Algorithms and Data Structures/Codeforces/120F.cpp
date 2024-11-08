// https://codeforces.com/contest/120/problem/F
// https://codeforces.com/problemset/problem/120/F

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;
bool graph[101][101], fix[101];
int bfs(){
    queue<pair<int, int> > q;
    int curr = 1;
    int dpth = 0;
    for(int i = 0; i <= 100; i++)
        fix[i] = false;
    q.push({curr, dpth});
    while(!q.empty()){
        pair<int, int> currPair = q.front();
        q.pop();
        curr = currPair.first;
        dpth = currPair.second;
        fix[curr] = true;
        for(int i = 0; i <= n; i++)
            if(graph[curr][i] && !fix[i])
                q.push({i, dpth + 1});
    }
    dpth = 0;
    for(int i = 0; i <= 100; i++)
        fix[i] = false;
    q.push({curr, dpth});
    while(!q.empty()){
        pair<int, int> currPair = q.front();
        q.pop();
        curr = currPair.first;
        dpth = currPair.second;
        fix[curr] = true;
        for(int i = 0; i <= n; i++)
            if(graph[curr][i] && !fix[i])
                q.push({i, dpth + 1});
    }
    return dpth;
}
int main(){
    freopen ("input.txt", "r", stdin);
	freopen ("output.txt", "w", stdout);
    cin >> t;
    int ans = 0;
    for(int h = 0; h < t; h++){
        for(int i = 0; i <= 100; i++)
            for(int j = 0; j <= 100; j++)
                graph[i][j] = false;
        cin >> n;
        for(int i = 0; i < n-1; i++){
            cin >> a >> b;
            graph[a][b] = true;
            graph[b][a] = true;
        }
        ans += bfs();
    }
    cout << ans << endl;
}