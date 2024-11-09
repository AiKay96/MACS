// https://codeforces.com/contest/482/problem/B
// https://codeforces.com/problemset/problem/482/B

#include <bits/stdc++.h>
using namespace std;
int l[100001], r[100001], q[100001], arr[100001], s[100001], sp[100001], ans[100001];

int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < m; i++)
        cin >> l[i] >> r[i] >> q[i];
    bool yes = true;
    for(int i = 0; i < 30; i++){
        for(int j = 0; j < 100001; j++)
            arr[j] = 0;
        for(int j = 0; j < m; j++){
            if(q[j] >> i & 1){
                arr[l[j]]++;
                arr[r[j] + 1]--;
            }
        }
        int t = 0;
        for(int j = 1; j <= n; j++){
            t += arr[j];
            s[j] = t;
            sp[j] = sp[j-1];
            if(t > 0){
                sp[j]++;
                ans[j] |= 1 << i;
            }
        }
        for(int j = 0; j < m; j++){
            if (!(q[j] >> i & 1)) {
                int x = l[j];
                int y = r[j];
                if (sp[y] - sp[x - 1] == y - x + 1) {
                    yes = false;
                    break;
                }
            }
        }
    }
    if (yes) {
        cout << "YES" << endl;
        for(int i = 1; i <= n; i++)
            cout << ans[i] << " ";
        cout << endl;
    } else {
        cout << "NO" << endl;
    }
    return 0;
}