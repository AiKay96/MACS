// https://codeforces.com/contest/848/problem/B
// https://codeforces.com/problemset/problem/848/B

#include<bits/stdc++.h>
using namespace std;
vector<int> v[200001];
int main() {
    ios_base::sync_with_stdio(false);
    int n, w, h;
    cin >> n >> w >> h;
    bool xze[n+1];
    int start[n+1];
    pair<int, int> ans[n+1];
    for(int i = 1; i <= n; i++){
        int type; cin >> type;
        if(type == 1)
            xze[i] = true;
        else
            xze[i] = false;
        int p, t; cin >> p >> t;
        v[p-t+100000].push_back(i);
        start[i] = p;
    }
    for(int j = 0; j <= 200000; j++){
        vector<pair<int, int> > xs;
        vector<pair<int, int> > ys;
        for(int i = 0; i < v[j].size(); i++){
            int curr = v[j][i];
            if(xze[curr])
                xs.push_back({start[curr], curr});
            else
                ys.push_back({-1*start[curr], curr});
        }
        sort(xs.begin(), xs.end());
        sort(ys.begin(), ys.end());
        vector<int> dancers;
        for(int i = 0; i < ys.size(); i++)
            dancers.push_back(ys[i].second);
        for(int i = 0; i < xs.size(); i++)
            dancers.push_back(xs[i].second);
        vector<int> pos;
        for(int i = 0; i < xs.size(); i++)
            pos.push_back(xs[i].first);
        for(int i = 0; i < ys.size(); i++)
            pos.push_back(-1*ys[i].first);
        for(int i = 0; i < dancers.size(); i++){
            if(i < xs.size())
                ans[dancers[i]] = {pos[i], h};
            else
                ans[dancers[i]] = {w, pos[i]};
        }
    }
    for(int i = 1; i <= n; i++){
        cout << ans[i].first << " " << ans[i].second << endl;
    }
}