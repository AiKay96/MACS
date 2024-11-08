// https://codeforces.com/contest/1063/problem/B
// https://codeforces.com/problemset/problem/1063/B

#include <bits/stdc++.h>
using namespace std;
int n, m, X, Y, l, r, labyrinth[2001][2001], dist[2001][2001];
priority_queue<pair<int, pair <int, int> > > pq;
bool inBounds(int x, int y){
    if(x >= n || y >=m || y <0 || x <0 || labyrinth[x][y] == 1){
        return false;
    }
    return true;
}
int main(){
    cin >> n >> m >> X >> Y >> l >> r;
    X--;
    Y--;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            char a;
            cin >> a;
            if(a == '*')
                labyrinth[i][j] = 1;
            dist[i][j] = INT_MAX;
        }
    }
    dist[X][Y] = 0;
    pq.push({0, {X, Y} });
    while(!pq.empty()){
        int x = pq.top().second.first;
        int y = pq.top().second.second;
        pq.pop();
        int dx = y - Y;
        int left = dist[x][y];
        int right = dx + left;
        //up
        if(inBounds(x-1, y) && left < dist[x-1][y]){
            dist[x-1][y] = left;
            pq.push({-dist[x-1][y], {x-1, y}});
        }
        //down
        if(inBounds(x+1, y) && left < dist[x+1][y]){
            dist[x+1][y] = left;
            pq.push({-dist[x+1][y], {x+1, y}});
        }
        //left
        if(left < l && inBounds(x, y-1) && left+1 < dist[x][y-1]){
            dist[x][y-1] = left+1;
            pq.push({-dist[x][y-1], {x, y-1}});
        }
        //right
        if(right < r && inBounds(x, y+1) && left < dist[x][y+1]){
            dist[x][y+1] = left;
            pq.push({-dist[x][y+1], {x, y+1}});
        }
    }
    int ans = 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(dist[i][j] != INT_MAX)
                ans++;
    cout << ans << endl;
}