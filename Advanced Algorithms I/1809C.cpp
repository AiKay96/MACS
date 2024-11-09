// https://codeforces.com/contest/1809/problem/C
// https://codeforces.com/problemset/problem/1809/C

#include<bits/stdc++.h>
using namespace std;
vector<int> getArr(int n, int k){
    if(n == 0)
       return vector<int>(n+1, -1); 
    if(k >= n){
        vector<int> ans = getArr(n-1, k-n);
        ans.push_back(1000);
        return ans;
    }else{
        vector<int> vec(n+1, -1);
        vec[k] = 50;
        vec[k+1] = -70;
        return vec;
    }
    return vector<int>();
}
int main() {
    ios_base::sync_with_stdio(false);
    int t;
    cin >> t;
    for(int p = 0; p < t; p++){
        int n, k;
        cin >> n >> k;
        vector<int> ans = getArr(n, k);
        for(int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    }
}