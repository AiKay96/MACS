// https://codeforces.com/contest/166/problem/B
// https://codeforces.com/problemset/problem/166/B

#include "bits/stdc++.h"
using namespace std;

#define int long long
int ax[100010], ay[100010];

int check(int x1, int y1, int x2, int y2, int x3, int y3) {
	return x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2);
}

int main() {
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	    cin >> ax[i] >> ay[i];
	int m;
	cin >> m;
	for(int i = 0; i < m; i++){
		int x, y;
		cin >> x >> y;
		if (check(ax[0], ay[0], ax[1], ay[1], x, y) >= 0) {
			cout << "NO" << endl;
			return 0;
		}
		if (check(ax[0], ay[0], ax[n - 1], ay[n - 1], x, y) <= 0) {
			cout << "NO" << endl;
			return 0;
		}
		int l = 1, r = n - 1;
		while (l != r) {
			int m = (l + r) / 2;
			if (check(ax[0], ay[0], ax[m], ay[m], x, y) < 0) {
				l = m + 1;
			}
			else r = m;
		}
		if (check(ax[l - 1], ay[l - 1], ax[l], ay[l], x, y) >= 0) {
			cout << "NO" << endl;
			return 0;
		}
	}
	cout << "YES" << endl;
}