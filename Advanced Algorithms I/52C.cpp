// https://codeforces.com/contest/52/problem/C
// https://codeforces.com/problemset/problem/52/C

#include<bits/stdc++.h>
using namespace std;

long long ltree[800005], rtree[800005], wtree[800005],ttree[800005];

long long get(long long l, long long r, long long k){
	if (ltree[k] >= l && rtree[k] <= r)
		return wtree[k] + ttree[k];
	if (ltree[k] > r || rtree[k] < l)
		return LLONG_MAX;
	long long mid = (ltree[k] + rtree[k]) / 2;
	long long le = get(l, r, k * 2);
	long long ri = get(l, r, k * 2 + 1);
	return min(le, ri) + ttree[k];
}
void update(long long k, long long w, long long l, long long r){
	long long le = ltree[k];
	long long ri = rtree[k];
	if (le >= l && ri <= r){
		ttree[k] += w;
		return;
	}
	long long mid = (le + ri) / 2;
	if (l <= mid)
	    update(k * 2, w, l, r);
	if (r > mid)
	    update(k * 2 + 1, w, l, r);
	wtree[k] = min(wtree[k * 2] + ttree[k * 2], wtree[k * 2 + 1] + ttree[k * 2 + 1]);
	return;
}
void build(long long l, long long r, long long k){
	ltree[k] = l;
	rtree[k] = r;
	if (l == r){
	    cin >> wtree[k];
		return;
	}
	long long mid = (l + r) / 2;
	build(l, mid, k * 2);
	build(mid + 1, r, k * 2 + 1);
	wtree[k] = min(wtree[k * 2], wtree[k * 2 + 1]);
}
int main(){
    int n, m;
	cin >> n;
	build(1, n, 1);
	cin >> m;
	for (int i = 0; i < m; i++){
	    long long x, y;
		cin >> x >> y;
		x++;
		y++;
		char c;
		cin.get(c);
		if (c == '\n'){
			if (x <= y)
			    cout << get(x, y, 1) << endl;
			else
			    cout << min(get(x, n, 1), get(1, y, 1)) << endl;
		}else{
		    long long q;
			cin >> q;
			if (x <= y){
			    update(1, q, x, y);
			} else {
			    update(1, q, x, n);
			    update(1, q, 1, y);
			}
		}
	}
}