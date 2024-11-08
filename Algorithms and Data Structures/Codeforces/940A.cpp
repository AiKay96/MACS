// https://codeforces.com/contest/940/problem/A
// https://codeforces.com/problemset/problem/940/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, d;
    cin >> n >> d;
    vector<int>  v;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    sort(v.begin(), v.end());
    int ans = n;
    int r = 0;
    for(int i = 0; i < n; i++){
        int num = v[i];
        for(int j = r; j < n; j++){
            if(v[i] + d < v[j]){
                break;
            }
            r++;
        }
        int tmp = n - (r - i);
        ans = min (ans, tmp);
    }
    cout << ans << endl;
}