// https://codeforces.com/contest/14/problem/D
// https://codeforces.com/problemset/problem/14/D

#include <bits/stdc++.h>
using namespace std;
 
int ans, n;
int a[201], b[201];
vector<int> graph[201], v;
int furthest, furthestCity;
 
void dfs(int curr, int from, int dist)
{
    if(dist > furthest){
        furthest = dist;
        furthestCity = curr;
    }
    for(int i = 0 ; i < graph[curr].size() ; i++)
        if(graph[curr][i] != from)
            dfs(graph[curr][i], curr, dist + 1);
}

void removeRoad(int i){
    for(int j = 1 ; j <= n ; j++)
            graph[j] = v;
    for(int j = 1 ; j < n ; j++)
        if(j != i){
            graph[a[j]].push_back(b[j]);
            graph[b[j]].push_back(a[j]);
        }
}

int findPath(int from){
    furthest = -1;
    dfs(from, -1 , 0);
    dfs(furthestCity, -1 , 0);
    return furthest;
}
 
int main()
{
    cin >> n;
    int ans = 0;
    for(int i = 1 ; i < n ; i++)
        cin >> a[i] >> b[i];
    for(int i = 1 ; i < n ; i++){
        removeRoad(i);
        int path1 = findPath(a[i]);
        int path2 = findPath(b[i]);
        ans = max(ans, path1 * path2);
    }
    
    cout<< ans <<endl;
}