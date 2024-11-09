// https://codeforces.com/contest/219/problem/D
// https://codeforces.com/problemset/problem/219/D

#include <bits/stdc++.h>
using namespace std;

bool visited1[200001];
bool visited2[200001];
vector<int> graph[200001];
vector<int> invgraph[200001];
int ans;
vector<int> vec;
vector<int> v;

int dfs(int curr)
{
    if (visited1[curr])
        return 0;
        
    int ans = 0;
    visited1[curr] = true;
    
    for(int i = 0; i < invgraph[curr].size(); i++){
        if(!visited1[invgraph[curr][i]]){
            ans++;
            ans += dfs(invgraph[curr][i]);
        }
    }
    for(int i = 0; i < graph[curr].size(); i++)
        if(!visited1[graph[curr][i]])
            ans += dfs(graph[curr][i]);
    
    return ans;
}
 

void dfs2(int curr, int res)
{
    if(res < ans) {
        ans = res;
        vec = v;
    }
    if(res == ans) {
        vec.push_back(curr);
    }
    
    visited2[curr] = true;
    
    for(int i = 0; i < graph[curr].size(); i++){
        if(!visited2[graph[curr][i]])
            dfs2(graph[curr][i], res + 1);
    }
    
    for(int i = 0; i < invgraph[curr].size(); i++){
        if(!visited2[invgraph[curr][i]])
            dfs2(invgraph[curr][i], res - 1);
    }
}
 
 
int main()
{
    int n;
    cin >> n;
    for(int i=0; i < n-1; i++){
        int from, to;
        cin >> from >> to;
        from--;
        to--;
        graph[from].push_back(to);
        invgraph[to].push_back(from);
    }
    
    ans = dfs(0);
    dfs2(0, ans);
    cout << ans <<endl;
    
    sort(vec.begin(), vec.end());
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] + 1 <<' ';
}