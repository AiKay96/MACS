// https://codeforces.com/contest/1620/problem/E
// https://codeforces.com/problemset/problem/1620/E

#include <bits/stdc++.h>
using namespace std;

vector<int> pos[500013];

int main() {
    ios_base::sync_with_stdio(false);
    int q;
    cin >> q;
    vector<int> v;
    int ind = 0;
    
    for(int i = 0; i < q; i++){
        int t, x, y;
        cin >> t;
        if (t == 1) {
            cin >> x;
            pos[x].push_back(ind);
            ind++;
        } else {
            cin >> x >> y;
            if (x != y) {
                if (pos[x].size() > pos[y].size())
                    pos[x].swap(pos[y]);
                for (int i = 0; i < pos[x].size(); i++)
                    pos[y].push_back(pos[x][i]);
                pos[x] = v;
            }
        }
    }
    
    vector<int> ans(ind);  
    for (int x = 0; x < 500013; x++)
        for (int i = 0; i < pos[x].size(); i++) 
            ans[pos[x][i]] = x;
  
    for (int i = 0; i < ind; i++) {
        cout << ans[i] << " ";
    }
}