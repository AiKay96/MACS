// https://codeforces.com/contest/148/problem/C
// https://codeforces.com/problemset/problem/148/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, oh, wow;
    cin >> n >> oh >> wow;
    vector<int> fortunes;
    if (wow > 0) {
        int current_sum = 2;
        fortunes.push_back(2);
        for (int i = 0; i < wow; i++) {
            fortunes.push_back(current_sum + 1);
            current_sum += current_sum + 1;
        }
    } else {
        if (oh > 0) {
            fortunes.push_back(2);
            fortunes.push_back(1);
        }
    }
    for (int i = 0; i < oh; i++)
        fortunes.push_back(max(3, fortunes.back() + 1));
    while (fortunes.size() < n) 
        fortunes.push_back(1);
    if (fortunes.size() > n) {
        cout << "-1" << endl;
    } else {
        for (int i = 0; i < n; i++) {
            cout << fortunes[i];
            if (i < n - 1)
                cout << " ";
        }
        cout << endl;
    }
    return 0;
}