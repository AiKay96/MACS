// https://codeforces.com/contest/827/problem/B
// https://codeforces.com/problemset/problem/827/B

#include <bits/stdc++.h>
using namespace std;
int t, n, m, k, a, b, c, d;
int main(){
    std::ios::sync_with_stdio(false);
    cin >> n >> k;
    vector<pair <int, int> > edges;
    queue<int> q;
    int curr = 1;
    int count = 1;
    for(int i = 0; i < k; i++){
        count++;
        edges.push_back({curr, count});
        q.push(count);
    }
    while(count < n){
        count++;
        curr = q.front();
        q.pop();
        edges.push_back({curr, count});
        q.push(count);
    }
    int maxDpth = (n - 1 + k - 1) / k;
    if((n - 2)%k == 0)
        maxDpth += maxDpth - 1;
    else
        maxDpth*=2;
    cout << maxDpth << endl;
    for(int i = 0; i < n-1; i++){
        cout << edges[i].first << " " << edges[i].second << endl;
    }
}