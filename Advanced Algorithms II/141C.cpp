// https://codeforces.com/contest/141/problem/C
// https://codeforces.com/problemset/problem/141/C

#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<string, int>> people(n);
    for (int i = 0; i < n; i++) 
        cin >> people[i].first >> people[i].second;
    sort(people.begin(), people.end(), 
         [](const auto& p1, const auto& p2) {
             return p1.second < p2.second;
         });
    for (int i = 0; i < n; i++) {
        if (people[i].second > i) {
            cout << "-1" << endl;
            return 0;
        }
    }
    vector<pair<string, int>> res;
    for (int i = 0; i < n; i++) 
        res.insert(res.begin() + people[i].second, {people[i].first, n - i});
    for (int i = 0; i < res.size(); i++) 
        cout << res[i].first << " " << res[i].second << endl;
}