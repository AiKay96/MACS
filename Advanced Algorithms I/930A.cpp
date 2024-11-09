// https://codeforces.com/contest/930/problem/A
// https://codeforces.com/problemset/problem/930/A

#include <bits/stdc++.h>
using namespace std;
 
int cnt[100001];
vector<int> vec[100001];
 
void dfs(int curr, int t){
    cnt[t]++;
    t++;
    for(int i=0; i < vec[curr].size(); i++)
        dfs(vec[curr][i], t);
}
 
int main(){
    int n;
    cin >> n;
    
    for(int i = 1; i < n; i++){
        int a;
        cin >> a;
        vec[a-1].push_back(i);
    }
    
    dfs(0,0);
    
    int ans = 0;
    for(int i = 0; i < n; i++)
        ans += cnt[i] % 2;
    
    cout << ans << endl;
}