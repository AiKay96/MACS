// https://codeforces.com/contest/356/problem/A
// https://codeforces.com/problemset/problem/356/A

#include<bits/stdc++.h>
using namespace std;
 
int main() {
    ios_base::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    int arr[n+1];
    set<int> knights;
    for(int i = 1; i <= n; i++){
        arr[i] = 0;
        knights.insert(i);
    }
    for(int k = 0; k < m; k++){
        int l, r;
        cin >> l >> r;
        int winner;
        cin >> winner;
        set<int>::iterator it = knights.lower_bound(l);
        while(it != knights.end() && *it <= r){
            arr[*it] = winner;
            knights.erase(it++);
        }
        knights.insert(winner);
        arr[winner] = 0;
    }
    for(int i = 1; i <= n; i++)
        cout << arr[i] << " ";
    cout << endl;
}