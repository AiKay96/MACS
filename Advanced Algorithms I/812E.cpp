// https://codeforces.com/contest/812/problem/E
// https://codeforces.com/problemset/problem/812/E

#include<bits/stdc++.h>
#define int long long
using namespace std;
int arr[100001], tree[100001];
vector<int> child[100001];
main() {
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i = 1; i <= n; i++)
        cin >> arr[i];
    for(int i = 2; i <= n; i++){
        cin >> tree[i];
        child[tree[i]].push_back(i);
    }
    queue<pair <int, int> > q;
    q.push({1, 0});
    int done = 0;
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        done = max(done, curr.second);
        for(int i = 0; i < child[curr.first].size(); i++)
            q.push({child[curr.first][i], curr.second + 1});
    }
    int nashti = done % 2;
    int ans = 0;
    int luwebze = 0;
    vector<int> sameluwze(10000001, 0);
    vector<int> samekentze(10000001, 0);
    vector<int> lvl(n+2, 0);
    q.push({1, 0});
    while(!q.empty()){
        pair<int, int> curr = q.front();
        q.pop();
        if(curr.second % 2 == nashti){
            ans ^= arr[curr.first];
            luwebze++;
            sameluwze[arr[curr.first]]++;
            lvl[curr.first] = 2;
        }else{
            lvl[curr.first] = 1;
            samekentze[arr[curr.first]]++;
        }
        for(int i = 0; i < child[curr.first].size(); i++)
            q.push({child[curr.first][i], curr.second + 1});
    }
    if(ans == 0){
        int realAns = (luwebze * (luwebze - 1))/2;
        int kentebze = n - luwebze;
        realAns += (kentebze * (kentebze - 1))/2;
        for(int i = 0; i < 10000001; i++){
            realAns += sameluwze[i] * samekentze[i];
        }
        cout << realAns << endl;
    }else{
        int realAns = 0;
        vector<int> ansxora;
        for(int i = 1; i <= n; i++){
            if(lvl[i] == 2 && sameluwze[arr[i]] > 0){
                ansxora.push_back(arr[i] ^ ans);
            }
        }
        for(int i = 0; i < ansxora.size(); i++){
            if(ansxora[i] <= 10000000)
                realAns += samekentze[ansxora[i]];
            
        }
        cout << realAns << endl;
    }
}