// https://codeforces.com/contest/1753/problem/A1
// https://codeforces.com/problemset/problem/1753/A1

#include <bits/stdc++.h>
using namespace std;
int t, n;
int main(){
    ios_base::sync_with_stdio(false);
    cin >> t;
    for(int h = 0; h < t; h++){
        cin >> n;
        int arr[n];
        for(int i = 0; i < n; i++){
            cin >> arr[i];
        }
        vector<pair<int, int> > v;
        if(n % 2 == 0){
            for(int i = 0; i < n; i+= 2){
                if(arr[i] == arr[i+1]){
                    v.push_back({i+1, i+2});
                }else{
                    v.push_back({i+1, i+1});
                    v.push_back({i+2, i+2});
                }
            }
            cout << v.size() << endl;
            for(int i = 0; i < v.size(); i++){
                cout << v[i].first << " " << v[i].second << endl;
            }
        }else{
            cout << -1 << endl;
        }
    }
}