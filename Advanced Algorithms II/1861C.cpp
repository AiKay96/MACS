// https://codeforces.com/contest/1861/problem/C
// https://codeforces.com/problemset/problem/1861/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int t;
    cin >> t;
    for (int i = 0; i < t; i++) {
        string ops;
        cin >> ops;

        int minLen = 0; 
        int currLen = 0;
        int unsortedInd = 0;
        bool invalid = false;

        for (char op : ops) {
            if (op == '+') {
                currLen++;
                if (currLen == 1)
                    minLen = 1;
            } 
            else if (op == '-') {
                currLen--;
                if (minLen > currLen)
                    minLen = currLen;
                if (unsortedInd > currLen)
                    unsortedInd = 0;
            } 
            else if (op == '1') {
                if (unsortedInd != 0) {
                    invalid = true;
                    break;
                }
                minLen = currLen;
            } 
            else {
                if (minLen == currLen) {
                    invalid = true;
                    break;
                }
                if (unsortedInd == 0)
                    unsortedInd = currLen;
            }
        }

        if (invalid) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
}