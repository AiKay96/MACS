// https://codeforces.com/contest/339/problem/D
// https://codeforces.com/problemset/problem/339/D

#include <bits/stdc++.h>
using namespace std;
int tree[300000];
void update(int ind, bool isOr){
    if(ind == 0)
        return;
    if(isOr)
        tree[ind] = tree[ind * 2] | tree[ind * 2 + 1];
    else 
        tree[ind] = tree[ind * 2] ^ tree[ind * 2 + 1];
    update(ind/2, !isOr);
}
int main(){
    int n, m;
    cin>> n >> m;
    int sz = 1 << n;
    for(int i = sz; i < 2*sz; i++){
        int a;
        cin >> a;
        tree[i] = a;
        update(i/2, true);
    }
    for(int i = 0; i < m; i++){
        int p, q;
        cin >> p >> q;
        int ind = sz - 1 + p;
        tree[ind] = q;
        update(ind/2, true);
        cout << tree[1] << endl;
    }
}