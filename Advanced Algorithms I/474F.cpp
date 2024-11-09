// https://codeforces.com/contest/474/problem/F
// https://codeforces.com/problemset/problem/474/F

#include <bits/stdc++.h>
using namespace std;
struct item{
    int mini;
    int num;
    int gcdu;
};
item tree[500000];
int pow2;
 
void update(int x){
    tree[x].mini = min(tree[2*x].mini, tree[2*x + 1].mini);
    tree[x].num = 0;
    if(tree[x].mini == tree[2*x].mini)
        tree[x].num += tree[2*x].num;
    if(tree[x].mini == tree[2*x + 1].mini)
        tree[x].num += tree[2*x + 1].num;
    tree[x].gcdu = __gcd(tree[2*x].gcdu, tree[2*x + 1].gcdu);
    if(x <= 1)
        return;
    update(x/2);
}
pair<int, int> summin(int x, int lx, int rx, int l, int r){
    if(l <= lx && rx <= r){
        return {tree[x].mini, tree[x].num};
    }
    if(l > rx || r < lx)
        return {INT_MAX, 0};
    pair<int, int> marcxniv = summin(2*x, lx, (lx + rx) / 2, l, r);
    pair<int, int> marjvniv = summin(2*x + 1, (lx + rx + 1) / 2, rx, l, r);
    int mini = min(marcxniv.first, marjvniv.first);
    int num = 0;
    if(mini == marcxniv.first)
        num += marcxniv.second;
    if(mini == marjvniv.first)
        num += marjvniv.second;
    return {mini, num};
}
 
int sumgcd(int x, int lx, int rx, int l, int r){
    if(l <= lx && rx <= r)
        return tree[x].gcdu;
    if(l > rx || r < lx)
        return 0;
    int marcxniv = sumgcd(2*x, lx, (lx + rx) / 2, l, r);
    int marjvniv = sumgcd(2*x + 1, (lx + rx + 1) / 2, rx, l, r);
    if(marcxniv == 0)
        marcxniv = marjvniv;
    return __gcd(marcxniv, marjvniv);
}
int main(){
    ios_base::sync_with_stdio(false);
    int n;
    cin >> n;
    pow2 = 1;
    while(pow2 < n)
        pow2 *= 2;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        tree[pow2+i].mini = a;
        tree[pow2+i].gcdu = a;
        tree[pow2+i].num = 1;
        update((pow2 + i) / 2);
    }
    int m;
    cin >> m;
    for(int i = 0; i < m; i++){
        int l, r;
        cin >> l >> r;
        int gcdu = sumgcd(1, 1, pow2, l, r);
        pair<int, int> ans = summin(1, 1, pow2, l, r);
        if(gcdu == ans.first)
            cout << r - l - ans.second + 1 << endl;
        else
            cout << r - l + 1 << endl;
    }
}