// https://codeforces.com/contest/767/problem/C
// https://codeforces.com/problemset/problem/767/C

#include<bits/stdc++.h>
using namespace std;
int w[1000001], sum[1000001], p[1000001], n;
vector<int> arr[1000001];
vector<int> cut;
bool f;
bool dfs(int curr, int num){
    bool found = false;
    for(int i = 0; i < arr[curr].size(); i++)
        found |= dfs(arr[curr][i], num);
    if(!found && sum[curr] == num){
        cut.push_back(curr);
        return true;
    }
    return found;
}

bool findInSubTrees(int num){
    int root = arr[0][0];
    for(int i = 0; i < arr[root].size(); i++){
        dfs(arr[root][i], num);
    }
    if(cut.size() == 1){
        num *= 2;
        for(int i = 0; i < cut.size(); i++){
            if(n == 6159)
            cout << cut[i] << endl;
        }
        int curr = p[cut[0]];
        while (curr != root){
            if (sum[curr] == num){
                cut.push_back(curr);
                break;
            }
            curr = p[curr];
        }
        if(cut.size() == 1)
            return false;
        else
            return true;
    }else if(cut.size() == 0){
        return false;
    }
    return true;
}

int sumdfs(int curr){
	sum[curr] = w[curr];
	for (int i = 0; i < arr[curr].size(); i++){
		sumdfs(arr[curr][i]);
		sum[curr] += sum[arr[curr][i]];
	}
	return sum[curr];
}

int main() {
    ios_base::sync_with_stdio(false);
    cin >> n;
    for(int i = 1; i <= n; i++){
        int a, k;
        cin >> a >> k;
        arr[a].push_back(i);
        p[i] = a;
        w[i] = k;
    }
    int ans = sumdfs(arr[0][0]);
    if(ans % 3 == 0){
        int num = ans / 3;
        if(findInSubTrees(num)){
            cout << cut[0] << " " << cut[1] << endl;
        }else{
            cout << -1 << endl;
        }
    }else{
        cout << -1 << endl;
    }
}