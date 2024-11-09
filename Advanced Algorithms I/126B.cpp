// https://codeforces.com/contest/126/problem/B
// https://codeforces.com/problemset/problem/126/B

#include<bits/stdc++.h>
using namespace std;

vector<int> zf(string str){
    int l = 0;
    int r = 0;
    int n = str.size();
    vector<int> v(n+3);
    for(int i = 1; i < n; i++){
        if(i < r)
            v[i] = min(r-i, v[i-l]);
        while(i + v[i] < n && str[v[i]] == str[i + v[i]])
            v[i]++;
        if(i + v[i] > r){
            r = i + v[i];
            l = i;
        }
    }
    return v;
}
int main() {
    ios_base::sync_with_stdio(false);
    string str;
    cin >> str;
    vector<int> ans = zf(str);
    int endmin = 0;
    int endmax = 0;
    int mid = 0;
    for(int i = str.size() - 1; i >= 0; i--){
        if(ans[i] + i == str.size()){
            endmin = endmax;
            endmax = max(endmax, ans[i]);
        }else{
            mid = max(ans[i], mid);
        }
    }
    string anss;
    if(mid >= endmax){
        anss = str.substr(0, endmax);
    }else{
        anss = str.substr(0, endmin);
    }
    if(anss == "")
        cout << "Just a legend" << endl;
    else
        cout << anss << endl;
}