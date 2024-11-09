// https://codeforces.com/contest/1549/problem/C
// https://codeforces.com/problemset/problem/1549/C

#include<bits/stdc++.h>
using namespace std;
int edges[200001], badFriends[200001];
int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int u, v;
        cin >> u >> v;
        edges[u]++;
        edges[v]++;
        badFriends[max(u,v)]++;
    }
    int ans = 0;
    for(int i = 1; i <= n; i++)
        if(edges[i] == badFriends[i])
            ans++;
    int q;
    cin >> q;
    for(int k = 0; k < q; k++){
        int t;
        cin >> t;
        if(t == 3){
            cout << ans << endl;
        }
        if(t == 2){
            int u, v;
            cin >> u >> v;
            if(badFriends[min(u,v)] == edges[min(u, v)])
                ans--;
            edges[u]--;
            edges[v]--;
            badFriends[max(u,v)]--;
            if(badFriends[min(u,v)] == edges[min(u, v)])
                ans++;
        }
        if(t == 1){
            int u, v;
            cin >> u >> v;
            if(badFriends[min(u,v)] == edges[min(u, v)])
                ans--;
            edges[u]++;
            edges[v]++;
            badFriends[max(u,v)]++;
            if(badFriends[min(u,v)] == edges[min(u, v)])
                ans++;
        }
    }
}