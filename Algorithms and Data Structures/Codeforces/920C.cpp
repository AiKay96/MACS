// https://codeforces.com/contest/920/problem/C
// https://codeforces.com/problemset/problem/920/C

#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> v;
    for(int i = 0; i < n; i++){
        int a;
        cin >> a;
        v.push_back(a);
    }
    string s;
    cin >> s;
    int leftMax = v[0];
    for(int i = 1; i < n; i++){
        if(s[i-1] == '0'){
            if(leftMax > i){
                cout << "NO" << endl;
                break;
            }
        }
        if(i == n-1)
            cout << "YES" << endl;
        leftMax = max(leftMax, v[i]);    
    }
}