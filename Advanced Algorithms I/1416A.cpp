// https://codeforces.com/contest/1416/problem/A
// https://codeforces.com/problemset/problem/1416/A

#include<bits/stdc++.h>
using namespace std;
vector<int> v, kudebi;
void findKudebi(){
    for(int i = v.size() - 1; i >= 0; i--){
        if(kudebi[v[i]] == 0){
            kudebi[v[i]] = v.size() - i;
        }
    }
}
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int h = 0; h < t; h++){
        int n;
        cin >> n;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            v.push_back(a);
        }
        for(int i = 0; i <= n; i++)
            kudebi.push_back(0);
        findKudebi();
        vector<int> prevInd(n+1, -1);
        vector<int> ans(n+1, 0);
        for(int i = 0; i < n; i++){
            ans[v[i]] = max(ans[v[i]], i - prevInd[v[i]]);
            prevInd[v[i]] = i;
        }
        for(int i = 0; i <n; i++)
            ans[i] = max(ans[i], kudebi[i]);
        v.clear();
        kudebi.clear();
        vector<int> rans(n+1, -1);
        for(int i = 1; i <= n; i++){
            if(rans[ans[i]] == -1)
                rans[ans[i]] = i;
        }
        for(int i = 2; i <= n; i++){
            if(rans[i] == -1)
                rans[i] = rans[i-1];
            else{
                if(rans[i-1] != -1)
                    rans[i] = min(rans[i], rans[i-1]);
            }
        }
        for(int i = 1; i <= n; i++)
            cout << rans[i] << " ";
        cout << endl;
    }
}