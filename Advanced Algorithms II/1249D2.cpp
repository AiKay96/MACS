// https://codeforces.com/contest/1249/problem/D2
// https://codeforces.com/problemset/problem/1249/D2

#include<bits/stdc++.h>
using namespace std;

int l[200001],r[200001];
vector<pair<int,int> > pos[200001];
vector<int> del;
set<pair<int,int> > inds;
int main()
{
    int n, k;
    cin >> n >> k;
    for(int i = 1; i <= n; i++){
        cin >> l[i] >> r[i];
        pos[l[i]].push_back({r[i], i});
    }
    for(int i = 1; i <= 200000; i++){
        for(int j = 0; j < pos[i].size(); j++)
			inds.insert(pos[i][j]);
        while(!inds.empty() && inds.begin()->first < i)
			inds.erase(inds.begin());
        while(inds.size() > k){
            auto it = inds.end();
            it--;
            del.push_back(it->second);
            inds.erase(it);
        }
    }
    cout << del.size() << endl;
    for(int i = 0; i < del.size(); i++)
        cout << del[i] << " ";
}