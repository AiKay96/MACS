// https://codeforces.com/contest/117/problem/C
// https://codeforces.com/problemset/problem/117/C

#include <bits/stdc++.h>
using namespace std;

string graph[5001];
bool used[5001];
int n;

bool dfs(int curr, int prev){
	if (used[curr]) 
	    return false;
	used[curr] = true;
	for (int i = 0; i < n; i++){
		if (prev != -1 && graph[curr][i] == '1' && graph[i][prev] == '1'){
		    cout << prev + 1 << " " << curr + 1 << " " << i + 1 << endl;
			return true;
		}
		if (graph[curr][i] == '1')
			if (dfs(i, curr)) 
			    return true;
	}
	return false;
}
int main(){
    ios::sync_with_stdio(false);
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> graph[i];
    for(int i = 0; i < n; i++){
        if(!used[i])
            if(dfs(i, -1))
                return 0;
    }
    cout << -1 << endl;
}