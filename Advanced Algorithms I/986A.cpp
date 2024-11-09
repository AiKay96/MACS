// https://codeforces.com/contest/986/problem/A
// https://codeforces.com/problemset/problem/986/A

#include <bits/stdc++.h>
using namespace std;
long long p = 1000000007;
long long dp[100001];
int main(){
    ios_base::sync_with_stdio(false);
    int n, m, k, s;
    cin >> n >> m >> k >> s;
    vector<int> v;
    vector<vector<int> > productCity(k+1, v);
    for(int i = 1; i <= n; i++){
        int a;
        cin >> a;
        productCity[a].push_back(i);
    }
    vector<vector<int> > edges(n+1, v);
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    vector<int> maxi(n+1, INT_MAX);
    vector<vector<int> > ans(k+1, maxi);
    for(int i = 1; i <= k; i++){
        vector<bool> been(n+1, false);
        queue<pair<int, int> > q;
        for(int j = 0; j < productCity[i].size(); j++)
            q.push({productCity[i][j], 0});
        while(!q.empty()){
            pair<int, int> curr = q.front();
            q.pop();
            if(been[curr.first])
                continue;
            been[curr.first] = true;
            ans[i][curr.first] = curr.second;
            for(int j = 0; j < edges[curr.first].size(); j++)
                q.push({edges[curr.first][j], curr.second + 1});
        }
    }
    for(int i = 1; i <= n; i++){
        vector<int> sasort;
        for(int j = 1; j <= k; j++)
            sasort.push_back(ans[j][i]);
        sort(sasort.begin(), sasort.end());
        int sum = 0;
        for(int j = 0; j < s; j++)
            sum += sasort[j];
        cout << sum << " ";
    }
    cout << endl;
}