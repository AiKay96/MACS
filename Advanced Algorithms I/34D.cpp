// https://codeforces.com/contest/34/problem/D
// https://codeforces.com/problemset/problem/34/D

#include<bits/stdc++.h>
using namespace std;
vector<int> graph[50001];
int ans[50001];
void dfs(int curr, int p){
    ans[curr] = p;
    for(int i = 0; i < graph[curr].size(); i++)
        if(graph[curr][i] != p)
            dfs(graph[curr][i], curr);
}
int main() {
    ios_base::sync_with_stdio(false);
    int n, c1, c2;
    cin >> n >> c1 >> c2;
    for(int i = 1; i <= n; i++){
        if(i == c1)
            continue;
        int p;
        cin >> p;
        graph[p].push_back(i);
        graph[i].push_back(p);
    }
    dfs(c2, 0);
    for(int i = 1; i <= n; i++)
        if(i != c2)
            cout << ans[i] << " ";
    cout << endl;
}