// https://codeforces.com/contest/1734/problem/A
// https://codeforces.com/problemset/problem/1734/A

#include <bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin >> t;
    for(int r = 0; r < t; r++){
        int n;
        cin >> n;
        vector<int> vc;
        for(int i = 0; i < n; i++){
            int a;
            cin >> a;
            vc.push_back(a);
        }
        sort(vc.begin(), vc.end());
        int arr[n];
        for(int i = 1; i < n; i++){
            arr[i] = vc[i] - vc[i-1];
        }
        int minChanges = INT_MAX;
        for(int i = 2; i < n; i++)
            minChanges = min (arr[i] + arr[i-1], minChanges);
        cout << minChanges << endl;
    }
}