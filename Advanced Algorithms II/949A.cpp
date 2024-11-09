// https://codeforces.com/contest/949/problem/A
// https://codeforces.com/problemset/problem/949/A

#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    
    vector<vector<int>> ans;
    vector<int> zeros;
    vector<int> ones;
    
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == '1') {
            if (zeros.empty()) {
                cout << -1;
                return 0;
            }
            int seqIdx = zeros[zeros.size() - 1];
            zeros.resize(zeros.size() - 1);
            ones.push_back(seqIdx);
            ans[seqIdx].push_back(i + 1);
        } else {
            if (!ones.empty()) {
                int seqIdx = ones[ones.size() - 1];
                ones.resize(ones.size() - 1);
                zeros.push_back(seqIdx);
                ans[seqIdx].push_back(i + 1);
            } else {
                zeros.push_back(ans.size());
                ans.push_back(vector<int>());
                ans[zeros[zeros.size() - 1]].push_back(i + 1);
            }
        }
    }
    
    if (!ones.empty()) {
        cout << -1;
        return 0;
    }
    
    cout << ans.size() << endl;
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i].size();
        for (int j = 0; j < ans[i].size(); j++) {
            cout << " " << ans[i][j];
        }
        cout << endl;
    }
    
    return 0;
}