// https://codeforces.com/contest/282/problem/B
// https://codeforces.com/problemset/problem/282/B

#include<bits/stdc++.h>
using namespace std;
int main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<pair<pair<int, int>, int> > v;
    long long bsum = 0;
    for(int i = 0; i < n; i++){
        int a, b;
        cin >> a >> b;
        v.push_back({{a,b}, i});
        bsum += b;
    }
    sort(v.begin(), v.end());
    long long a = 0;
    vector<char> ans (n, 'G');
    int ind  = 0;
    while(abs(a - bsum) > 500){
        a += v[ind].first.first;
        ans[v[ind].second] = 'A';
        bsum -=v[ind].first.second;
        ind++;
    }
    for(int i = 0; i < n; i++)
        cout << ans[i];
    cout << endl;
}