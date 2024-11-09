// https://codeforces.com/contest/622/problem/C
// https://codeforces.com/problemset/problem/622/C

#include <bits/stdc++.h>
using namespace std;

vector<int> x(200010), nextSame(200010);

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int n, queries;
    cin >> n >> queries;

    for (int i = 1; i <= n; i++)
        cin >> x[i];

    nextSame[n] = n + 1;
    for (int i = n - 1; i >= 1; i--) {
        if (x[i] == x[i + 1])
            nextSame[i] = nextSame[i + 1];
        else
            nextSame[i] = i + 1;
    }

    for (int i = 0; i < queries; i++) {
        int left, right, value;
        cin >> left >> right >> value;

        if (x[left] != value) {
            cout << left << endl;
        } else {
            if (nextSame[left] > right)
                cout << -1 << endl;
            else
                cout << nextSame[left] << endl;
        }
    }

    return 0;
}