// https://codeforces.com/contest/1795/problem/F
// https://codeforces.com/problemset/problem/1795/F

#include <bits/stdc++.h>
using namespace std;
int n, m, counter;
vector<vector<int> > v;
vector<int> reds;
vector<int> dp;
vector<int> moves;
vector<int> r;
bool ans;
void dfs(int curr, int parent){
    if(!ans)
        return;
    if(v[curr].size() == 1){
        if(reds[curr] == 1)
            dp[curr] = moves[curr];
        else
            dp[curr] = -1;
        return;
    }
    for(int i = 0; i < v[curr].size(); i++)
        if(v[curr][i] != parent)
            dfs(v[curr][i], curr);
    if(!ans)
        return;
    int mini = INT_MAX;
    int maxi1 = INT_MIN;
    int maxi2 = INT_MIN;
    for(int i = 0; i < v[curr].size(); i++){
        if(v[curr][i] != parent){
            if(dp[v[curr][i]] >= maxi1){
                maxi2 = maxi1;
                maxi1 = dp[v[curr][i]];
            }else if(dp[v[curr][i]] >= maxi2){
                maxi2 = dp[v[curr][i]];
            }
            mini = min(mini, dp[v[curr][i]]);
        }
    }
    if(reds[curr] == 1){
        if(maxi1 > 0)
            ans = false;
        dp[curr] = 0;
        if(mini + moves[curr] > 0)
            dp[curr] = moves[curr];
    }else{
        if(maxi1 > 0 && maxi2 > 0)
            ans = false;
        if(maxi1 > 0)
            if(maxi1 - 1 + mini > 0)
                dp[curr] = maxi1 - 1;
            else
                dp[curr] = 0;
        else
            dp[curr] = mini - 1;
    }
}
bool check(int x){
    for(int i = 0; i < m; i++)
        moves[r[i]] = x/m;
    for(int i = 0; i < x % m; i++)
        moves[r[i]]++;
    ans = true;
    dfs(1, 1);
    return ans && dp[1] <= 0;
}
int main(){
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        vector<int> tmp;
        cin >> n;
        vector<vector<int> > tmp2(n+1, tmp);
        v = tmp2;
        r = tmp;
        vector<int> tmp3(n+1, 0);
        reds = tmp3;
        dp = tmp3;
        moves = tmp3;
        for(int i = 1; i < n; i++){
            int a, b;
            cin >> a >> b;
            v[a].push_back(b);
            v[b].push_back(a);
        }
        v[1].push_back(1);
        cin >> m;
        for(int i = 0; i < m; i++){
            int a;
            cin >> a;
            reds[a] = 1;
            r.push_back(a);
        }
        int l = 0;int r = n;
		while(r > l + 1){
			int mid = (l + r) / 2;
			if (check(mid))
				l = mid;
			else
				r = mid;
		}
		cout << l << endl;
    }
}