// https://codeforces.com/contest/522/problem/D
// https://codeforces.com/problemset/problem/522/D

#include<bits/stdc++.h>
using namespace std;
int tree[1050000], pow2, lefts[500001], rights[500001];
void update(int x){
    tree[x] = min(tree[2*x], tree[2*x + 1]);
    if(x <= 1)
        return;
    update(x/2);
}
int sum(int x, int lx, int rx, int l, int r){
    if(l <= lx && rx <= r)
        return tree[x];
    if(r <= lx || rx <= l)
        return INT_MAX;
    return min(sum(2*x, lx, (lx + rx) / 2, l, r), sum(2*x + 1, (lx + rx) / 2, rx, l, r));
}
void coutTree(){
    for(int i = 1; i < 2*pow2; i++)
        cout << tree[i] << " ";
    cout << endl;
}
int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int arr[n], answers[m];
    map<int, int> mp;
    for(int i = 1; i <= n; i++){
        cin >> arr[i];
        lefts[i] = mp[arr[i]];
        rights[mp[arr[i]]] = i;
        mp[arr[i]] = i; 
    }
    vector<pair<pair<int, int>, int> > v;
    for(int i = 0; i < m; i++){
        int a, b;
        cin >> a >> b;
        v.push_back({{b, a}, i});
    }
    sort(v.begin(), v.end());
    pow2 = 1;
    while(pow2 < n)
        pow2 *= 2;
    for(int i = 0; i < pow2; i++){
        tree[pow2+i] = INT_MAX;
        update((pow2 + i) / 2);
    }
    int prev = 1;
    for(int k = 0; k < v.size(); k++){
        int currMax = v[k].first.first;
        for(int i = prev; i <= currMax; i++){
            if(rights[i] != 0 && rights[i] <= currMax){
                tree[pow2 + i - 1] = rights[i] - i;
                update((pow2 + i - 1) / 2);
            }
            if(lefts[i] != 0 && lefts[i] < prev){
                tree[pow2 + lefts[i] - 1] = i - lefts[i];
                update((pow2 + lefts[i] - 1) / 2);
            }
        }
        int ans = sum(1, 0, pow2, v[k].first.second - 1, v[k].first.first);
        if(ans == INT_MAX)
            ans = -1;
        answers[v[k].second] = ans;
        prev = currMax + 1;
    }
    for(int i = 0; i < m; i++)
        cout << answers[i] << endl;
}