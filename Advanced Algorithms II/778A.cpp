// https://codeforces.com/contest/778/problem/A
// https://codeforces.com/problemset/problem/778/A

#include <bits/stdc++.h>
using namespace std;

bool isSubsequence(string& t, string& p, vector<int>& a, int m) {
    vector<bool> removed(t.length(), false);
    for (int i = 0; i < m; i++) 
        removed[a[i] - 1] = true;
    int j = 0;
    for (int i = 0; i < t.length() && j < p.length(); i++)
        if (!removed[i] && t[i] == p[j]) 
            j++;
    return j == p.length();
}

int main() {
    string t, p;
    cin >> t >> p;
    vector<int> a(t.length());
    for (int i = 0; i < t.length(); i++)
        cin >> a[i];
    int left = 0;
    int right = t.length();
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (isSubsequence(t, p, a, mid))
            left = mid;
        else 
            right = mid - 1;
    }
    cout << left << endl;
}